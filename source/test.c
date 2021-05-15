#include <criterion/criterion.h>
#include "../include/minishell.h"
#include <signal.h>

/*
Test(category, nom, .signal = SIGSEGV)
{
	// .signal = SIGSEGV , pour compter les segfaults comme valide
	cr_assert(0 == false);
}
*/


t_prompt create_prompt_with_env(void)
{
	t_prompt prompt;
	prompt.env = NULL;
	char *expected[] = {"USER=mbeaujar", "MAIL=user@user.ft",
						"TERM=iterm2leplusbeau", "PWD=jesuisla", NULL};

	addlstenv(&prompt.env, expected[0]);
	addlstenv(&prompt.env, expected[1]);
	addlstenv(&prompt.env, expected[2]);
	addlstenv(&prompt.env, expected[3]);
	return (prompt);
}

Test(export, search)
{
	char *expected = "MAIL";
	t_prompt prompt = create_prompt_with_env();
	t_env *find = search_min(prompt.env);
	int diff = ft_strcmp(expected, find->name);
	freelstenv(prompt.env);
	cr_expect(diff == 0);
}

Test(env, delete)
{
}

Test(env, strjoin)
{
	char *expected = "USER=mbeaujar";
	char *output = ft_strjoin_env("USER", "mbeaujar");
	int diff = strcmp(expected, output);
	cr_expect(diff == 0);
	free(output);
}

Test(env, strjoin_seg)
{
	char *expected = "ENV=";
	char *output = ft_strjoin_env("ENV", "");
	int diff = strcmp(expected, output);
	cr_expect(diff == 0);
	free(output);
}

Test(env, strjoin_segfault)
{
	char *expected = "=maison";
	char *output = ft_strjoin_env("", "maison");
	int diff = strcmp(expected, output);
	cr_expect(diff == 0);
	free(output);
}

Test(env, strjoin_segfault_again)
{
	char *expected = "NAME=";
	char *output = ft_strjoin_env("NAME", NULL);
	int diff = strcmp(expected, output);
	cr_expect(diff == 0);
	free(output);
}

Test(env, new_table_env)
{
	int i = 0;
	t_prompt prompt = create_prompt_with_env();
	char *expected[] = {"USER=mbeaujar", "MAIL=user@user.ft",
						"TERM=iterm2leplusbeau", "PWD=jesuisla", NULL};
	char **envp = new_table_env(prompt.env);
	while (envp[i])
	{
		if ((strcmp(envp[i], expected[i])) != 0)
		{
			free_tab(envp);
			freelstenv(prompt.env);
			cr_assert(0);
		}
		i++;
	}
	freelstenv(prompt.env);
	free_tab(envp);
	cr_assert(1);
}

Test(env, create_env)
{
	char *s1 = "PWD";
	char *s2 = "/vivelavie";
	char *expected = "PWD=/vivelavie";
	char *env = ft_create_env(s1, s2, FREE_NOT);
	int diff = strcmp(expected, env);
	free(env);
	cr_expect(!diff);
}

Test(prompt, buffer)
{
	t_prompt prompt;

	prompt.indice = 2;
	char *str = ft_strdup("bonjour");
	int len = 40;
	char *output = new_size_buffer(&prompt, 'i', str, len);
	char *expected = "boinjour";
	int diff = strcmp(expected, output);
	cr_expect(!diff);
	free(output);
}

Test(export, strcmp)
{
	char s1[] = "USER";
	char s2[] = "MAIL";
	int diff = ft_strcmp(s1, s2);
	//printf("diff : %d\n", diff);
	cr_expect(diff > 0);
}

Test(env, create_env_null)
{
	t_env *head;

	head = NULL;
	char str[] = "RA";
	addlstenv(&head, ft_strdup(str));
	if (head == NULL)
		cr_assert(0);
	//printf("name : %s value : %s\n", head->name, head->value);
	int diff = ft_strcmp(head->name, str);
	cr_expect(diff == 0);
	free(head->name);
	free(head);
}

//-----------------------------------------------------------------------------------//


int ft_strcmp_lexer(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s2[i] < 0)
			s2[i] = -s2[i];
		if (s2[i] != s1[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int test_token(t_prompt *prompt, char *str, char *expected[])
{
	t_lexer *head = lexer(prompt, str);
	t_lexer *tmp = head;
	if (!head)
	{
/* 		printlexer(&prompt, str);
		printf("\n"); */
		return(-1);
	}
	int len = ft_strlen_tab(expected);
	if (len != lstsizelexer(head))
	{
/* 		printf("\n-------------\nexpected : \n");
		for(int i = 0; expected[i]; i++)
			printf("'%s'\n", expected[i]);
		printf("output : \n");
		printlstlexer(head); */
		freelstlexer(&head);
		return (0);
	}
	for (int i = 0; i < len; i++)
	{
		if (ft_strcmp_lexer(expected[i], tmp->token) != 0)
		{
			freelstlexer(&head);
			printf("expected : %s --- ouput : %s\n", expected[i], tmp->token);
			return (0);
		}
		tmp = tmp->next;
	}
	freelstlexer(&head);
	return (1);
}

Test(lexer_token, create_token_difficutl)
{
	t_prompt prompt;
	char str[] = "ls bon\" jour\" 'je suis la''oui' \"moi    aussi\"";
	char *expected[] = {"ls", "bon jour",
						"je suis laoui", "moi    aussi", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_simple)
{
	t_prompt prompt;
	char str[] = "< Makefile cat | cat";
	char *expected[] = {"<", "Makefile",
						"cat", "|", "cat", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_1)
{
	t_prompt prompt;
	char str[] = "echo \\b";
	char *expected[] = {"echo", "b", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_2)
{
	t_prompt prompt;
	char str[] = "echo \"\\b\"";
	char *expected[] = {"echo", "\\b", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_3)
{
	t_prompt prompt;
	char str[] = "echo '\\b'";
	char *expected[] = {"echo", "\\b", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_4)
{
	t_prompt prompt;
	char str[] = "'je suis la''oui'";
	char *expected[] = {"je suis laoui", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_5)
{
	t_prompt prompt;
	// \e"xp"'o'\rt
	char str[] = "\\e\"xp\"'o'\\rt";
	char *expected[] = {"export", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_6)
{
	t_prompt prompt;
	// echo "quatre"\ 'arguments'\ \en" un"
	char str[] = "echo \"quatre\"\\ 'arguments'\\ \\en\" un\"";
	char *expected[] = {"echo", "quatre arguments en un", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_7)
{
	t_prompt prompt;
	// "e""c""h""o"
	char str[] = "\"e\"\"c\"\"h\"\"o\"";
	char *expected[] = {"echo", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_8)
{
	t_prompt prompt;
	char str[] = "          echo";
	char *expected[] = {"echo", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_9)
{
	t_prompt prompt;
	char str[] = "echo           ";
	char *expected[] = {"echo", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_10)
{
	t_prompt prompt;
	char str[] = "echo\\ a";
	char *expected[] = {"echo a", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_11)
{
	t_prompt prompt;
	char str[] = "ls \"\" bonjour";
	char *expected[] = {"ls", "", "bonjour", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_12)
{
	t_prompt prompt;
	char str[] = "ls";
	char *expected[] = {"ls", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_13)
{
	t_prompt prompt;
	char str[] = "ls \\";
	char *expected[] = {"ls", NULL};
	cr_expect(test_token(&prompt, str, expected) == 0);
}

Test(lexer_token, create_token_14)
{
	t_prompt prompt;
	char str[] = "ls \"";
	char *expected[] = {"ls", NULL};
	cr_expect(test_token(&prompt, str, expected) == -1);
}

Test(lexer_token, create_token_15)
{
	t_prompt prompt;
	char str[] = "ls '";
	char *expected[] = {"ls", NULL};
	cr_expect(test_token(&prompt, str, expected) == -1);
}

Test(lexer_token, create_token_16)
{
	t_prompt prompt;
	char str[] = "echo \"coment ca va ' toto '\n\"";
	char *expected[] = {"echo", "coment ca va ' toto '\n", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_17)
{
	t_prompt prompt;
	char str[] = "echo bon \" jour\"";
	char *expected[] = {"echo", "bon", " jour", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_18)
{
	t_prompt prompt;
	// \e\c\h\o \b\o\n\j\o\u\r
	char str[] = "\\e\\c\\h\\o \\b\\o\\n\\j\\o\\u\\r";
	char *expected[] = {"echo", "bonjour",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_20)
{
	t_prompt prompt;
	// echo " '\ ' "
	char str[] = "echo \" \'\\ \' \"";
	char *expected[] = { "echo", " \'\\ \' ",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_21)
{
	t_prompt prompt;
	// echo "\ "
	char str[] = "echo \"\\ \"";
	char *expected[] = { "echo", "\\ ",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

//--------------

Test(lexer_token, create_token_22)
{
	t_prompt prompt;
	// echo "\i "
	char str[] = "echo \"\\i \"";
	char *expected[] = { "echo", "\\i ",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_23)
{
	t_prompt prompt;
	// echo "\"
	char str[] = "echo \"\\\"";
	char *expected[] = { "echo", "\\",  NULL};
	cr_expect(test_token(&prompt, str, expected) == -1);
}

Test(lexer_token, create_token_24)
{
	t_prompt prompt;
	// echo "\\"
	char str[] = "echo \"\\\\\"";
	char *expected[] = { "echo", "\\",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_43)
{
	t_prompt prompt;
	// echo "'\'"
	char str[] = "echo \"\'\\\'\"";
	char *expected[] = { "echo", "\'\\\'",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_25)
{
	t_prompt prompt;
	// echo "'"
	char str[] = "echo \"\'\"";
	char *expected[] = { "echo", "\'",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_26)
{
	t_prompt prompt;
	// echo "' "'"
	char str[] = "echo \"\' \"\'\"";
	char *expected[] = { "echo", "\' \"\'",  NULL};
	cr_expect(test_token(&prompt, str, expected) == -1);
}

Test(lexer_token, create_token_27)
{
	t_prompt prompt;
	// echo "' \"'"
	char str[] = "echo \"\' \\\"\'\"";
	char *expected[] = { "echo", "' \"'",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_28)
{
	t_prompt prompt;
	// echo " ' \"' "
	char str[] = "echo \" \' \\\"\' \"";
	char *expected[] = { "echo", " \' \"\' ",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_29)
{
	t_prompt prompt;
	// echo   bon " jour"
	char str[] = "echo   bon \" jour\"";
	char *expected[] = { "echo", "bon", " jour",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_30)
{
	t_prompt prompt;
	// echo " '\"'"
	char str[] = "echo \" \'\\\"\'\"";
	char *expected[] = { "echo", " \'\"\'",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_31)
{
	t_prompt prompt;
	// echo ' "\" '
	char str[] = "echo \' \"\\\" \'";
	char *expected[] = { "echo", " \"\\\" ",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_32)
{
	t_prompt prompt;
	// echo ' "\"" '
	char str[] = "echo \' \"\\\"\" \'";
	char *expected[] = { "echo", " \"\\\"\" ",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_33)
{
	t_prompt prompt;
	// echo ' "\"" \' '\n'
	char str[] = "echo \' \"\\\"\" \\\' \'\\n\'";
	char *expected[] = { "echo", " \"\\\"\" \\",	"\\n",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_34)
{
	t_prompt prompt;
	// echo ' \\' '\n'
	char str[] = "echo \' \\\\\' \'\\n\'";
	char *expected[] = { "echo", " \\\\", "\\n",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_35)
{
	t_prompt prompt;
	// echo ' \\'
	char str[] = "echo \' \\\\\'";
	char *expected[] = { "echo", " \\\\",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_36)
{
	t_prompt prompt;
	// echo " '\'"
	char str[] = "echo \" \'\\\'\"";
	char *expected[] = { "echo", " \'\\\'",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_37)
{
	t_prompt prompt;
	// echo "\\\ "
	char str[] = "echo \"\\\\\\ \"";
	char *expected[] = { "echo", "\\\\ ",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_38)
{
	t_prompt prompt;
	// echo "\\\\\\\\\\\\\\\\\\ "
	char str[] = "echo \"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \"";
	char *expected[] = { "echo", "\\\\\\\\\\\\\\\\\\ ", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_39)
{
	t_prompt prompt;
	// echo "\\\\\\\\\\\\\\\\\ "
	char str[] = "echo \"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \"";
	char *expected[] = { "echo", "\\\\\\\\\\\\\\\\\\ ",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_40)
{
	t_prompt prompt;
	// echo "\\\\ "
	char str[] = "echo \"\\\\\\\\ \"";
	char *expected[] = { "echo", "\\\\ ",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_41)
{
	t_prompt prompt;
	// echo "\\\\\\ "
	char str[] = "echo \"\\\\\\\\\\\\ \"";
	char *expected[] = { "echo", "\\\\\\ ",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_42)
{
	t_prompt prompt;
	// \e\c\h\o \b\o\n\j\o\u\r
	char str[] = "\\e\\c\\h\\o \\b\\o\\n\\j\\o\\u\\r";
	char *expected[] = { "echo", "bonjour",  NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_44)
{
	t_prompt prompt;
	// ls bonjour;
	char str[] = "ls bonjour;";
	char *expected[] = { "ls", "bonjour", ";", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_45)
{
	t_prompt prompt;
	// ls bonjour;
	char str[] = "ls bonjour;ls|cat";
	char *expected[] = { "ls", "bonjour", ";", "ls", "|", "cat", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_46)
{
	t_prompt prompt;
	// ls bonjour;
	char str[] = "< file1 echo salut>file2";
	char *expected[] = { "<", "file1", "echo", "salut", ">", "file2", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_47)
{
	t_prompt prompt;
	// ls bonjour;
	char str[] = "< file1 ;|;|echo salut>file2";
	char *expected[] = { "<", "file1", ";", "|", ";", "|", "echo", "salut", ">", "file2", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_48)
{
	t_prompt prompt;
	// ls bonjour;
	char str[] = "echo salut <> file1";
	char *expected[] = { "echo", "salut", "<", ">", "file1", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_49)
{
	t_prompt prompt;
	// ls bonjour;
	char str[] = "echo salut << file1";
	char *expected[] = { "echo", "salut", "<<", "file1", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_50)
{
	t_prompt prompt;
	// ls bonjour;
	char str[] = "echo salut <<<< file1";
	char *expected[] = { "echo", "salut", "<<<<", "file1", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_51)
{
	t_prompt prompt;
	// ls bonjour;
	char str[] = "echo salut \"<\" \"|\" | '|' '<<<<<<' <<<<<>file1<file2";
	char *expected[] = { "echo", "salut", "<", "|", "|", "|", "<<<<<<", "<<<<<", ">", "file1", "<", "file2", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

Test(lexer_token, create_token_52)
{
	t_prompt prompt;
	// ls bonjour;
	char str[] = "echo ; \";\"";
	char *expected[] = { "echo", ";", ";", NULL};
	cr_expect(test_token(&prompt, str, expected));
}

//------------------------------------------------------------------//

Test(lexer_type, set_type_error_1)
{
	t_prompt prompt;
	char str[] = "echo < file1 salut ; < < ls > file2 arg1 arg2";
	t_lexer *head = lexer(&prompt, str);
	cr_expect(head == NULL);
	freelstlexer(&head);
}

Test(lexer_type, set_type_error_2)
{
	t_prompt prompt;
	char str[] = "echo < file1 salut >";
	t_lexer *head = lexer(&prompt, str);
	cr_expect(head == NULL);
	freelstlexer(&head);
}

Test(lexer_type, set_type_error_3)
{
	t_prompt prompt;
	char str[] = "echo < file1 salut <";
	t_lexer *head = lexer(&prompt, str);
	cr_expect(head == NULL);
	freelstlexer(&head);
}

Test(lexer_type, set_type_error_4)
{
	t_prompt prompt;
	char str[] = "echo < file1 salut |";
	t_lexer *head = lexer(&prompt, str);
	cr_expect(head == NULL);
	freelstlexer(&head);
}

Test(lexer_type, set_type_error_5)
{
	t_prompt prompt;
	char str[] = "; echo < file1 salut";
	t_lexer *head = lexer(&prompt, str);
	cr_expect(head == NULL);
	freelstlexer(&head);
}

Test(lexer_type, set_type_error_6)
{
	t_prompt prompt;
	char str[] = "echo < file1 <<< salut";
	t_lexer *head = lexer(&prompt, str);
	cr_expect(head == NULL);
	freelstlexer(&head);
}

