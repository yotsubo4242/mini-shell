assert() {
	# テストしようとしている内容をprint
	printf '%-30s:' "\"$1\""

	# bashの出力をcmpに保存
	echo -n -e "$1" | bash >cmp 2>&-
	# bashのexit statusをexpectedに代入
	expected=$?
	# minishellの出力をoutに保存
	echo -n -e "$1" | ./minishell >out 2>&-
	# minishellのexit statusをactualに代入
	actual=$?

	# bashとminishellの出力を比較
	diff cmp out >/dev/null && echo -n '  diff ok' || echo -n '  diff ng'

	# bashとminishellのexit statusを比較
	if [ "$actual" = "$expected" ]; then
		echo -n '  status ok'
	else
		echo -n "  status ng, expected $expected but got $actual"
	fi
	echo
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
