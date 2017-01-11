#include "Parser.hpp"

Parser::Parser()
{
	root = NULL;
	nb_leaves = 0;
	nb_depth = 0;
	initOp();
}

t_op				*Parser::createOp(int priority, binOpFn fn)
{
	t_op			*op;

	op = (t_op *)malloc(sizeof(t_op));
	op->priority = priority;
	op->fn = fn;
	return (op);
}

float				add(float lhs, float rhs) { return (lhs + rhs); }
float				sub(float lhs, float rhs) { return (lhs - rhs); }
float				mul(float lhs, float rhs) {	return (lhs * rhs); }
float				div(float lhs, float rhs) {	return (lhs / rhs); }

void				Parser::initOp()
{
	opMap["+"] = createOp(1, add);
	opMap["-"] = createOp(1, sub);
	opMap["*"] = createOp(2, mul);
	opMap["/"] = createOp(2, div);
	opMap["^"] = createOp(2, std::pow);
}

bool				checkNeg(char *str, int j)
{
	j--;
	while (j > 0 && (str[j] == ' ' || str[j] == '\t' || str[j] == '\n'))
	{
		j--;
	}
	if (str[j] == '+' || str[j] == '-' || str[j] == '*' || str[j] == '/' || str[j] == '(' || str[j] == ')')
		return (true);
	return (false);
}

int					Parser::tokenizer(char *str, char **tok, int *type)
{
	char			*token;
	static int		i = 0;
	int				j;
	int				l;

	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '\0')
		return (0);
	j = i;
	if ((str[i] >= 48 && str[i] <= 57) || str[i] == '.')
	{
		while ((str[i] >= 48 && str[i] <= 57) || str[i] == '.')
			i++;
		l = i - j;
		token = (char *)malloc(sizeof(char) * (l + 1));
		while (j != i)
		{
			token[l - (i - j)] = str[j];
			j++;
		}
		token[l] = '\0';
		*tok = token;
		*type = T_NBR;
	}
	else if (str[i] == '-')
	{
		j = i;
		if (j == 0 || checkNeg(str, j))
		{
			j = i + 1;
			while (str[j] != '\0' && (str[j] == ' ' || str[j] == '\t' || str[j] == '\n'))
			{
				j++;
			}
			if ((str[j] >= 48 && str[j] <= 57) || str[j] == '.')
			{
				i = j;
				while ((str[i] >= 48 && str[i] <= 57) || str[i] == '.')
					i++;
				l = i - j;
				token = (char *)malloc(sizeof(char) * (l + 2));
				token[0] = '-';
				while (j != i)
				{
					token[l - (i - j) + 1] = str[j];
					j++;
				}
				token[l + 1] = '\0';
				*tok = token;
				*type = T_NBR;
			}
			else
			{
				i = j;
				token = (char *)malloc(sizeof(char) * 2);
				token[0] = str[i];
				token[1] = '\0';
				i++;
				*tok = token;
				*type = T_OP;
			}

		}
		else
		{
			token = (char *)malloc(sizeof(char) * 2);
			token[0] = str[i];
			token[1] = '\0';
			i++;
			*tok = token;
			*type = T_OP;
		}

	}
	else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
	{
		token = (char *)malloc(sizeof(char) * 2);
		token[0] = str[i];
		token[1] = '\0';
		i++;
		*tok = token;
		*type = T_OP;
	}
	else if (str[i] == '(')
	{
		token = (char *)malloc(sizeof(char) * 2);
		token[0] = str[i];
		token[1] = '\0';
		i++;
		*tok = token;
		*type = T_SUB_ST;
	}
	else if (str[i] == ')')
	{
		token = (char *)malloc(sizeof(char) * 2);
		token[0] = str[i];
		token[1] = '\0';
		i++;
		*tok = token;
		*type = T_SUB_END;
	}
	else
	{
		token = (char *)malloc(sizeof(char) * 2);
		token[0] = '?';
		token[1] = '\0';
		i++;
		*tok = token;
		*type = T_UNKNOWN;
	}
	return (1);
}

void				deleteNode(t_tree *tree)
{
	if (tree == NULL)
		return;
	if (tree->lhp != NULL)
	{
		deleteNode(tree->lhp);
	}
	if (tree->rhp != NULL)
	{
		deleteNode(tree->rhp);
	}
	deleteNode(tree);
}

std::vector< int >	calcVal(int u0, int depth)
{
	std::vector< int>	vec;

	vec.push_back(u0 / 2);
	for (int i = 1 ; i < depth + 1 ; i++)
	{
		vec.push_back(u0);
		u0 = 2 * u0 + 1; 
	}
	return (vec);
}

void				printTreeMatrix(TreeMatrix mat)
{
	int				matSize = mat.size();
	int				margin = 10;
	int				span = std::pow(2, matSize - 1) - 1;
	int				lineSize = (std::pow(2, matSize - 1) + 1) * span + margin;
	std::string		line;
	std::string		display;
	std::vector< int>	val = calcVal(span, matSize);

	for (int i = 0 ; i < matSize ; i++)
	{
		int m = val[(matSize - i - 1)] +  margin;
		int s = val[(matSize - i)];
		line.clear();
		line.insert(line.begin(), lineSize, ' ');
		for (int j = 0; j < mat[i].size() ; j++)
		{
			int ind = m + j * (s + 1) - mat[i][j].size() / 2;
//			std::cout <<"lineSize: " << lineSize << "\t\t" << "ind :" << ind << "\t\t" 
//				<< "mat[i][j]: " << mat[i][j] << "\t" << "mat[i][j].size(): " << mat[i][j].size() << std::endl;
			line.replace(ind, mat[i][j].size(), mat[i][j], 0, mat[i][j].size());
		}
		line.append("\n\n");
		display.append(line);
	}
	std::cout << display << std::endl;
}

void				incMat(TreeMatrix *mat, int i)
{
	std::vector<std::string>	vec;

	if (mat->size() <= i)
	{
		vec.insert(vec.begin(), pow(2, i), " ");
		mat->push_back(vec);
	}
}

void				recPrint(TreeMatrix *mat, t_tree *node, int depth, int index)
{
	incMat(mat, depth);
	if (node == NULL)
		return ;
	if (node->lhp == NULL && node->rhp == NULL)
	{
		(*mat)[depth][index] = node->sym;
		return ;
	}
	recPrint(mat, node->lhp, depth + 1,  2 * index);
	recPrint(mat, node->rhp, depth + 1,  2 * index + 1);
		(*mat)[depth][index] = node->sym;
	return ;
}

void				displayTree(t_tree *node)
{
	TreeMatrix		mat;
	int				i = 0;

	std::cout << "Start recursif filling of matrix" << std::endl;
	recPrint(&mat, node, 0, 0);
	std::cout << "End recursif filling of matrix" << std::endl;
	std::cout << "Start printing of matrix" << std::endl;
	printTreeMatrix(mat);
	std::cout << "End printing of matrix" << std::endl;
}

std::string			Parser::evaluateNode(t_tree *node)
{
	std::string		lhsym;
	std::string		rhsym;

	if (node == NULL)
	{
		return ("?");
	}
	if (node->lhp == NULL && node->rhp == NULL)
	{
//		return (node->sym + ":"+ std::to_string(node->depth));
		return (node->sym);
	}
	lhsym = evaluateNode(node->lhp);
	rhsym = evaluateNode(node->rhp);
	return ("( " + lhsym + " " + node->sym + " " + rhsym + " )");
}

float				Parser::evaluateNodeInt(t_tree *node)
{
	float			lhval;
	float			rhval;

	if (node == NULL)
	{
		return (0);
	}
	if (node->lhp == NULL && node->rhp == NULL)
	{
		return (node->val);
	}
	lhval = evaluateNodeInt(node->lhp);
	rhval = evaluateNodeInt(node->rhp);
	return (opMap[node->sym]->fn(lhval, rhval));
}

void				Parser::evaluateRoot()
{
	if (root == NULL)
	{
		std::cout << "No tree to print." << std::endl;
	}
	else
	{
		std::cout << " = " << evaluateNodeInt(root) << std::endl;
	}
}

void				Parser::printTree()
{
	if (root == NULL)
	{
		std::cout << "No tree to print." << std::endl;
	}
	else
	{
		std::cout << "Tree gives: " << evaluateNode(root) ;
	}
}

t_tree				*Parser::createLeaf(char *str, int priority)
{
	t_tree			*leaf;

	leaf = (t_tree *)malloc(sizeof(t_tree));
	leaf->sym = str;
	if (priority == 3)
		leaf->val = std::stof(str);
	else
		leaf->val = 0;
	leaf->priority = priority;
	leaf->depth = tree_depth;
	leaf->lhp = NULL;
	leaf->rhp = NULL;
	return (leaf);
}

void				Parser::insertTreeLeaf(char *str, t_tree **tree)
{
	t_tree			*leaf;
	t_tree			*tree_root;

	leaf = createLeaf(str, 3);
	if (*tree == NULL)
		*tree = leaf;
	else if ((*tree)->lhp == NULL)
		(*tree)->lhp = leaf;
	else if ((*tree)->rhp == NULL)
		(*tree)->rhp = leaf;
	else
	{
		tree_root = *tree;
		while ((*tree)->rhp != NULL)
		{
			*tree = (*tree)->rhp;
		}
		(*tree)->rhp = leaf;
		*tree = tree_root;
	}
}

void				Parser::insertTreeNode(char *str, t_tree **tree)
{
	t_tree			*leaf;
	t_tree			*tree_root;

	if ((*tree) == NULL)
	{
		std::cout << "error cannot start by " << str << std::endl;
	}
	else
	{
		leaf = createLeaf(str, opMap[str]->priority);
		if (leaf->priority <= (*tree)->priority || (*tree)->depth != tree_depth)
		{
			leaf->lhp = (*tree);
			(*tree) = leaf;
		}
		else
		{
			tree_root = (*tree);
			while ((*tree)->rhp->rhp != NULL && (*tree)->rhp->depth == tree_depth)
			{
				(*tree) = (*tree)->rhp;
			}
			leaf->lhp = (*tree)->rhp;
			(*tree)->rhp = leaf;
			(*tree) = tree_root;
		}
	}
}

void				Parser::insertSubTree(t_tree *subTree, t_tree **tree)
{
	t_tree			*tree_root;

	if ((*tree) == NULL)
	{
		(*tree) = subTree;
	}
	else if ((*tree)->rhp == NULL)
	{
		(*tree)->rhp = subTree;
	}
	else
	{
		tree_root = (*tree);
		while ((*tree)->rhp != NULL)
		{
			(*tree) = (*tree)->rhp;
		}
		(*tree)->rhp = subTree;
		(*tree) = tree_root;
	}
}

t_tree				*Parser::createSubTree(char *str)
{
	t_tree			*tree;
	t_tree			*subTree;
	char			*token;
	int				type;

	tree = NULL;
	tree_depth++;
	std::cout << "Start of sub-tree" << std::endl;
	while (tokenizer(str, &token, &type))
	{
		std::cout << "Token of type " << type << ": {" << token << "}" << std::endl;
		switch (type)
		{
			case T_NBR:
				nb_leaves++;
				insertTreeLeaf(token, &tree);
				break;
			case T_OP:
				insertTreeNode(token, &tree);
				break;
			case T_SUB_ST:
				subTree = createSubTree(str);
				insertSubTree(subTree, &tree);
				break;
			case T_SUB_END:
				delete (token);
				tree_depth--;
				std::cout << "End of sub-tree" << std::endl;
				return (tree);
			case T_UNKNOWN:
				std::cout << "unknown token." << std::endl;
				break;
		}
		delete (token);
	}
	tree_depth--;
	std::cout << "End of sub-tree" << std::endl;
	return (tree);
}

void				Parser::parseStrToScreen(char *str)
{
	t_tree			*tree;

	tree_depth = 0;
	tree = createSubTree(str);
	root = tree;

	printTree();
	evaluateRoot();
	displayTree(root);
}
