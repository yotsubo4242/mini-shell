
# def color
RESET='\033[0m'
RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
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

cleanup() {
	rm -f cmp out a.out print_args exit42 infinite_loop no_exec_perm no_read_perm
}

assert() {
	COMMAND="$1"
	shift
	printf '%-60s:' "[$COMMAND]"
	# exit status
	echo -n -e "$COMMAND" | bash >cmp 2>&-
	expected=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".cmp"
	done
	echo -n -e "$COMMAND" | ./minishell >out 2>&-
	acutual=$?
	for arg in "$@"
	do
		mv "$arg" " $arg"".out"
	done

	diff cmp out >/dev/null  && echo -e -n " diff $OK" || echo -e -n " diff $NG"

	if [ "$acutual" = "$expected" ]; then 
		echo -e -n " status $OK"
	else
		echo -e -n " status $NG, expected $expected but got $acutual"
	fi

	for arg in "$@"
	do
		echo -n " [$arg] "
		diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
	done	
	echo
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




cleanup
