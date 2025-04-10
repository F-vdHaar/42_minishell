


# include "parser.h"

void expand_tokens(t_token **tokens, t_env *env);

void expand_tokens(t_token **tokens, t_env *env)
{
	(void)env;
	(void)tokens;
}

t_env *init_env(char **envp)
{
	t_env *env_list = NULL;
	(void)envp;
	//t_env *new;

//	while (*envp)
//	{
	// 	char **split = ft_split(*envp, '='); // [ "PATH", "/usr/bin" ]
	// 	if (split && split[0])
	// 	{
	// 		new = malloc(sizeof(t_env));
	// 		new->key = ft_strdup(split[0]);
	// 		new->value = split[1] ? ft_strdup(split[1]) : ft_strdup("");
	// 		new->exported = 1;
	// 		new->next = env_list;
	// 		env_list = new;
	// 	}
	// 	ft_free_split(split); // Free the char** created by ft_split
	// 	envp++;
	// }
	return (env_list);
}
