#ifndef PARSER_HPP
# define PARSER_HPP

# include <string>
# include <map>
# include <vector>
# include <iostream>
# include <cmath>

# define T_UNKNOWN		0
# define T_NBR			1
# define T_OP			2
# define T_SUB_ST		3
# define T_SUB_END		4


typedef struct			s_op
{
	int					priority;
	float				(*fn)(float, float);
}						t_op;

typedef struct			s_tree
{
	std::string			sym;
	float				val;
	int					priority;
	int					depth;
	s_tree				*lhp;
	s_tree				*rhp;
}						t_tree;

typedef std::map<const std::string, t_op *> Op;
typedef std::vector< std::vector<std::string> > TreeMatrix;
typedef float (*binOpFn)(float, float);

class					Parser
{
	public:
						Parser();
		void			parseStrToScreen(char *str);

	private:
		void			initOp();
		t_op			*createOp(int priority, binOpFn fn);

		int				tokenizer(char *str, char **token, int *type);
		t_tree			*createLeaf(char *str, int priority);
		std::string		evaluateNode(t_tree *node);
		float			evaluateNodeInt(t_tree *node);
		void			printTree();
		void			evaluateRoot();

		void			insertTreeLeaf(char *str, t_tree **tree);
		void			insertTreeNode(char *str, t_tree **tree);
		void			insertSubTree(t_tree *subTree, t_tree **tree);
		t_tree			*createSubTree(char *str);


	private:
		t_tree			*root;
		Op				opMap;
		int				tree_depth;
		int				nb_leaves;
		int				nb_depth;
};


#endif
