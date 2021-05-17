#only inside the container

# echo "---------------LEXER TEST---------------"
# gcc tester/lexer.c -lcriterion -lncurses -L. -ltester -Llibft -lftlinux -o test
# ./test

echo "---------------PARSER TEST--------------"
gcc tester/parser.c -lcriterion -lncurses -L. -ltester -Llibft -lftlinux -o test
./test

# echo "---------------PROMPT TEST--------------"
# gcc tester/prompt.c -lcriterion -lncurses -L. -ltester -Llibft -lftlinux -o test
# ./test

