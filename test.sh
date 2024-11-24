assert() {
    # 色の定義
    GREEN='\033[32m'
    RED='\033[31m'
    RESET='\033[0m'

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
        printf " ${GREEN}diff ok${RESET}"
    else
        printf " ${RED}diff ng${RESET}"
    fi

    # statusの結果を色付きで表示
    if [ "$actual" = "$expected" ]; then
        printf " ${GREEN}status ok${RESET}\n"
    else
        printf " ${RED}status ng, expected $expected but got $actual${RESET}\n"
    fi
}
# empty line (eof)
assert ''

# hello
assert 'hello'

# absolute path commands
assert '/bin/pwd'
assert '/bin/echo'

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

# Expand Variable
assert 'echo $USER'
assert 'echo $USER$PATH$TERM'
assert 'echo "$USER  $PATH   $TERM"'

# Special Parameter $?
assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'
