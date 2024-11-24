
# def color
RESET='\033[0m'

BLACK='\033[30m'
RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
BLUE='\033[34m'
MAGENTA='\033[35m'
CYAN='\033[36m'
WHITE='\033[37m'

# def OK NG
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

print_section() {
	echo -e $CYAN"$1"$RESET
}

print_desc() {
	echo -e $YELLOW"$1"$RESET
}

assert() {

    # テストしようとしている内容をprint
    printf '%-30s:' "\"$1\""

    # bashの出力をcmpに保存
    echo -n -e "$1" | bash >cmp 2>&-
    expected=$?

    # minishellの出力をoutに保存
    echo -n -e "$1" | ./minishell >out 2>&-
    actual=$?

    # diffの結果を色付きで表示
    if diff cmp out >/dev/null; then
        printf " diff $OK"
    else
        printf " diff $NG"
    fi

    # statusの結果を色付きで表示
    if [ "$actual" = "$expected" ]; then
        printf " status $OK\n"
    else
        printf " status $NG, expected $expected but got $actual\n"
    fi
}
# empty line (eof)
assert ''

# hello
assert 'hello'

# absolute path commands
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

# generate executable
cat <<eof | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
eof

# search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

## no such command
assert 'a.out'
assert 'nosuchfile'

# command not found
assert '"'

# assert '.'  #. is a built in command in bash
assert '..'

# is a directory
assert './'
assert '/'
assert '/etc'
assert '/etc/'
assert '/////'

## Permission denied
echo "int main() { }" | gcc -xc -o no_exec_perm -
chmod -x no_exec_perm
assert 'no_exec_perm'
assert './no_exec_perm'
echo "int main() { }" | gcc -xc -o no_read_perm -
chmod -r no_read_perm
assert 'no_read_perm'
assert './no_read_perm'

mkdir -p /tmp/a tmp/b
echo "int main() { return 1; }" | gcc -xc -o /tmp/a/simple_test -
echo "int main() { return 2; }" | gcc -xc -o /tmp/b/simple_test -

print_desc "/tmp/a /tmp/b both with permission"
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

print_desc "a with permission, b without permission"
chmod +x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

print_desc "a without permission, b with permission"
chmod -x /tmp/a/simple_test; chmod +x /tmp/b/simple_test;
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'












# Expand Variable
assert 'echo $USER'
assert 'echo $USER$PATH$TERM'
assert 'echo "$USER  $PATH   $TERM"'

# Special Parameter $?
assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'
