#!/bin/bash
RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
RESET="\033[0m"
OK=$GREEN"OK"$RESET
NG=$RED"NG"$RESET

cat <<EOF | gcc -xc -o a.out -
#include <stdio.h>
int main() { printf("hello from a.out\n"); }
EOF

cat <<EOF | gcc -xc -o print_args -
#include <stdio.h>
int main(int argc, char *argv[]) {
	for (int i = 0; argv[i]; i++)
		printf("argv[%d] = [%s]\n", i, argv[i]);
}
EOF

cat <<EOF | gcc -xc -o exit42 -
int main() { return 42; }
EOF

print_desc() {
	echo -e $YELLOW"$1"$RESET
}

cleanup() {
	rm -f cmp out cmp_err out_err a.out print_args exit42 infinite_loop no_exec_perm no_read_perm pwd2.txt
}

assert() {
	COMMAND="$1"
	shift
	printf '%-70s:' "[$COMMAND]"
	# exit status
	echo -n -e "$COMMAND" | bash >cmp 2>cmp_err
	expected=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".cmp"
		# mv "$arg" "$arg"".cmp_err"
	done
	echo -n -e "$COMMAND" | ./minishell >out 2>out_err
	actual=$?
	for arg in "$@"
	do
		mv "$arg" "$arg"".out"
		# mv "$arg" "$arg"".out_err"
	done

	if diff out cmp > /dev/null; then
		echo -e -n "  diff $OK"
	else
		echo -e -n "  diff $NG"
		printf '%-70s:\n' "[$COMMAND]" >> error.log
		diff -U 1 out cmp >>error.log
	fi
	#
	# if diff out_err cmp_err > /dev/null; then
	# 	echo -e -n "  diff err $OK"
	# else
	# 	echo -e -n "  diff err $NG"
	# 	printf '%-70s:\n' "[$COMMAND]" >> error.log
	# 	diff -U 1 out_err cmp_err >>error.log
	#
	# fi
	if [ "$actual" = "$expected" ]; then
		echo -e -n "  status $OK"
	else
		echo -e -n "  status $NG, expected $expected but got $actual"
		printf '%-70s:' "[$COMMAND]" >>error.log
		echo "status NG, expected $expected but got $actual" >>error.log
	fi

	for arg in "$@"
	do
		echo -n "  [$arg] "
		diff "$arg"".cmp" "$arg"".out" >/dev/null && echo -e -n "$OK" || echo -e -n "$NG"
		rm -f "$arg"".cmp" "$arg"".out"
		rm -f "$arg"".cmp_err" "$arg"".out_err"
	done
	echo
}

rm -f error.log

# Empty line (EOF)
assert ''

# Only space tab
assert '\t'
assert ' '

# Absolute path commands without args 
assert '/bin/pwd'
assert '/bin/echo'
assert '/bin/ls'

# Absolute path commands with args 
assert '/bin/pwd ..'
assert '/bin/echo test.sh test.sh'
assert '/bin/ls src'

# Relative path comands without args
assert '/bin/../bin/pwd'
assert '/bin/../bin/echo'
assert '/bin/../bin/ls'

# Search command path without args
assert 'pwd'
assert 'echo'
assert 'ls'
assert './a.out'

## no such command
assert 'a.out'
assert 'nosuchfile'

## command not found
assert 'yeah'
assert '""'
# assert '.' # . is a builtin command in bash
assert '..'

## is a directory
assert './'
assert '/'
assert '/etc'
assert '/etc/'
assert '////'

## Permission denied
echo "int main() { }" | gcc -xc -o no_exec_perm -
chmod -x no_exec_perm
assert 'no_exec_perm'
assert './no_exec_perm'
echo "int main() { }" | gcc -xc -o no_read_perm -
chmod -r no_read_perm
assert 'no_read_perm'
assert './no_read_perm'

mkdir -p /tmp/a /tmp/b
echo "int main() { return 1; }" | gcc -xc -o /tmp/a/simple_test -
echo "int main() { return 2; }" | gcc -xc -o /tmp/b/simple_test -

print_desc "/tmp/a /tmp/b both with permission"
assert 'unset PATH\nexport PATH="/tmp/a:/tmp/b"\nsimple_test'
assert 'unset PATH\nexport PATH="/tmp/b:/tmp/a"\nsimple_test'

print_desc "/tmp/a /tmp/b both without permission"
chmod -x /tmp/a/simple_test; chmod -x /tmp/b/simple_test;
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

# Tokenize
## unquoted word
assert 'ls /'
assert 'echo hello    world     '
assert 'nosuchfile\n\n'

## single quote
assert "./print_args 'hello   world' '42Tokyo'"
assert "echo 'hello   world' '42Tokyo'"
assert "echo '\"hello   world\"' '42Tokyo'"
assert "./print_args 'ls | grep Makefile'"
assert "echo 'ls | grep Makefile'"

## double quote
assert './print_args "hello   world" "42Tokyo"'
assert 'echo "hello   world" "42Tokyo"'
assert "echo \"'hello   world'\" \"42Tokyo\""
assert './print_args "cat test.sh | cat > lol.c"'
assert "echo \"cat test.sh | cat > lol.c\""

## combination
assert "echo hello'      world'"
assert "echo hello'  world  '\"  42Tokyo  \""

# Redirect
## Redirecting output
assert 'echo hello >hello.txt' 'hello.txt'
assert 'echo hello >f1>f2>f3' 'f1' 'f2' 'f3'
assert 'echo hello >f1>>f2>f3' 'f1' 'f2' 'f3'

## Redirecting input
assert 'cat <Makefile'
echo hello >f1
echo world >f2
echo 42Tokyo >f3
assert 'cat <f1<f2<f3'
rm -f f1 f2 f3
assert 'cat <hoge'

## Appending Redirected output
assert 'pwd >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt >>pwd.txt' 'pwd.txt'
assert 'pwd >>pwd.txt >>pwd2.txt' 'pwd.txt'
assert 'pwd >>pwd.txt \n pwd >>pwd.txt' 'pwd.txt'

## Here Document
assert 'cat <<EOF\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF<<eof\nhello\nworld\nEOF\neof\nNOPRINT'
assert 'cat <<EOF\nhello\nworld'
assert 'cat <<E"O"F\nhello\nworld\nEOF\nNOPRINT'
assert 'cat <<EOF   \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<"EOF" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
assert 'cat <<EO"F" \n$USER\n$NO_SUCH_VAR\n$FOO$BAR\nEOF'
(
	print_desc 'export EOF="eof"'
	export EOF="eof"
	assert 'cat <<$EOF         \neof\n$EOF\nEOF'
	assert 'cat <<"$EOF"       \neof\n$EOF\nEOF'
)

# Pipe
assert 'cat Makefile | grep minishell | sort'
assert 'cat | cat | ls\n\n'
assert 'ls aefawefae | grep error | sort'

# Expand Variable
assert 'echo $USER'
assert 'echo $USER$PATH$TERM'
assert 'echo "$USER  $PATH   $TERM"'

# Special Parameter $?
assert 'echo $?'
assert 'invalid\necho $?\necho $?'
assert 'exit42\necho $?\necho $?'
assert 'exit42\n\necho $?\necho $?'
assert 'ls \nexit \necho $?'
assert 'expr $? + $?'

# Word Splitting
assert 'export FOO="echo hello"\n$FOO'
assert 'export TEST="cho -n"\ne$TEST'
assert 'export FOO="a       b"\necho $FOO'
assert 'export FOO="a       b"\necho hello$FOO'
assert 'export FOO="a       b"\necho $FOO"world"'
assert 'export FOO="a       b"\necho hello$FOO"world"'
assert 'export FOO="echo a      b"\n$FOO'

assert 'export IFS=""\nexport FOO="echo hello"\n$FOO'
assert 'export IFS=""\nexport TEST="cho -n"\ne$TEST'
assert 'export IFS=""\nexport FOO="a       b"\n./print_args $FOO'
assert 'export IFS=""\nexport FOO="a       b"\n./print_args hello$FOO'
assert 'export IFS=""\nexport FOO="a       b"\n./print_args $FOO"world"'
assert 'export IFS=""\nexport FOO="a       b"\n./print_args hello$FOO"world"'
assert 'export IFS=""\nexport FOO="./print_args a      b"\n$FOO'

assert 'export IFS="abc"\nexport FOO="./print_argsahellobbbbbbworldccc"\n$FOO'
assert 'export IFS="abc"\nexport TEST="choa-n"\ne$TEST'
assert 'export IFS="abc"\nexport FOO="xabcabcy"\n./print_args $FOO'
assert 'export IFS="abc"\nexport FOO="xabcabcy"\n./print_args hello$FOO'
assert 'export IFS="abc"\nexport FOO="xabcabcy"\n./print_args $FOO"world"'
assert 'export IFS="abc"\nexport FOO="xabcabcy"\n./print_args hello$FOO"world"'
assert 'export IFS="abc"\nexport FOO="./print_argsaaaaaxabcabcy"\n$FOO'

assert 'export IFS="a"\nexport FOO="aaahelloaaaworldaaa"\n./print_args $FOO'
assert 'export IFS="a "\nexport FOO="   hello   world   "\n./print_args $FOO'
assert 'export IFS="a "\nexport FOO=" a a hello a a world a a "\n./print_args $FOO'
assert 'export IFS="a "\nexport FOO="aaa"\n./print_args $FOO'
assert 'export IFS="a "\nexport FOO="helloaaa"\n./print_args $FOO'
assert 'export IFS="a "\nexport FOO="helloaaaworld"\n./print_args $FOO'
assert 'export IFS="a "\nexport FOO="aaahelloaaaworldaaa"\n./print_args $FOO'

assert 'export IFS=" :"\nexport FOO="hello: : :"\n./print_args $FOO'
assert 'export IFS=" :"\nexport FOO="hello: : : "\n./print_args $FOO'
assert 'export IFS=" :"\nexport FOO="hello : : :"\n./print_args $FOO'
assert 'export IFS=" :"\nexport FOO="hello : : : "\n./print_args $FOO'

assert 'export IFS=" :"\nexport FOO=": : :hello: : :"\n./print_args $FOO'
assert 'export IFS=" :"\nexport FOO=": : : hello: : : "\n./print_args $FOO'
assert 'export IFS=" :"\nexport FOO=" : : :hello : : :"\n./print_args $FOO'
assert 'export IFS=" :"\nexport FOO=" : : : hello : : : "\n./print_args $FOO'

assert 'export IFS=" :"\nexport FOO="hello: : :world"\n./print_args $FOO'
assert 'export IFS=" :"\nexport FOO="hello : : :world"\n./print_args $FOO'
assert 'export IFS=" :"\nexport FOO="hello: : : world"\n./print_args $FOO'
assert 'export IFS=" :"\nexport FOO="hello : : : world"\n./print_args $FOO'

assert 'echo "$IFS"'

print_desc 'export IFS=":"'
(
	export IFS=":"
	assert 'echo "$IFS"'
	assert 'export FOO="hello:world:42Tokyo"\n./print_args $FOO'
)

# # Signal handling
echo "int main() { while (1) ; }" | gcc -xc -o infinite_loop -

# ## Signal to shell processes
print_desc "SIGTERM to SHELL"
(sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

print_desc "SIGQUIT to SHELL"
(sleep 0.01; pkill -SIGQUIT bash; # SIGQUIT should not kill the shell
 sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGQUIT minishell; # SIGQUIT should not kill the shell
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

print_desc "SIGINT to SHELL"
(sleep 0.01; pkill -SIGINT bash; # SIGINT should not kill the shell
 sleep 0.01; pkill -SIGTERM bash;
 sleep 0.01; pkill -SIGINT minishell; # SIGINT should not kill the shell
 sleep 0.01; pkill -SIGTERM minishell) &
assert './infinite_loop' 2>/dev/null # Redirect stderr to suppress signal terminated message

## Signal to child processes
print_desc "SIGTERM to child process"
(sleep 0.01; pkill -SIGTERM infinite_loop;
 sleep 0.01; pkill -SIGTERM infinite_loop) &
assert './infinite_loop'

print_desc "SIGINT to child process"
(sleep 0.01; pkill -SIGINT infinite_loop;
 sleep 0.01; pkill -SIGINT infinite_loop) &
assert './infinite_loop'

print_desc "SIGQUIT to child process"
(sleep 0.01; pkill -SIGQUIT infinite_loop;
 sleep 0.01; pkill -SIGQUIT infinite_loop) &
assert './infinite_loop'

print_desc "SIGUSR1 to child process"
(sleep 0.01; pkill -SIGUSR1 infinite_loop;
 sleep 0.01; pkill -SIGUSR1 infinite_loop) &
assert './infinite_loop'

# Manual Debug
# $ ./minishell
# $ 
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ hogehoge
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# >
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D
#
# $ ./minishell
# $ cat <<EOF
# > hoge
# > fuga
# 1. Ctrl-\ 
# 2. Ctrl-C
# 3. Ctrl-D

# Builtin
## exit
assert 'exit'
assert 'exit 42'
assert 'exit -42'
assert 'exit +42'
assert 'exit ""'
assert 'exit hello'
assert 'exit 42Tokyo'
assert 'exit 1 2'
assert 'exit 9223372036854775806'
assert 'exit 9223372036854775807'
assert 'exit 9223372036854775808'
assert 'exit -9223372036854775807'
assert 'exit -9223372036854775808'
assert 'exit -9223372036854775809'

## export
print_desc "Output of 'export' differs, but it's ok."
assert 'export' # order of variables, default variables differs...
assert 'export | grep nosuch | sort'
assert 'export nosuch\n export | grep nosuch | sort'
assert 'export nosuch=fuga\n export | grep nosuch | sort'
assert 'export nosuch=fuga hoge=nosuch\n export | grep nosuch | sort'
assert 'export [invalid]'
assert 'export [invalid_nosuch]\n export | grep nosuch | sort'
assert 'export [invalid]=nosuch\n export | grep nosuch | sort'
assert 'export [invalid] nosuch hoge=nosuch\n export | grep nosuch | sort'
assert 'export nosuch [invalid] hoge=nosuch\n export | grep nosuch | sort'
assert 'export nosuch hoge=nosuch [invalid]\n export | grep nosuch | sort'
assert 'export nosuch="nosuch2=hoge"\nexport $nosuch\n export | grep nosuch | sort'
assert 'export a b c d \n export'
assert 'export e \n export'

## unset
(
	print_desc 'export hoge fuga=fuga'
	export hoge fuga=fuga
	assert 'unset'
	assert 'unset hoge'
	assert 'unset fuga'
	assert 'unset nosuch'
	assert 'unset [invalid]'
	assert 'unset hoge fuga'
	assert 'unset hoge nosuch fuga'
	assert 'unset fuga \n export | echo $fuga'
	assert 'unset [invalid] fuga \n echo $fuga'
)

## env
# print_desc "Output of 'env' differs, but it's ok."
# assert 'env' # shell level, PID, cant bee diff ok.
assert 'env | grep PWD | sort'

## cd
assert 'cd'
assert 'cd .'
assert 'cd ..'
assert 'cd ///'
assert 'cd /tmp'
assert 'cd /tmp/'
assert 'cd /tmp///'
assert 'cd /../../../././.././'
assert 'cd src'
assert 'unset HOME\ncd'

assert 'cd \n echo $PWD'
assert 'cd \n echo $PWD'
assert 'cd .\n echo $PWD'
assert 'cd ..\n echo $PWD'
assert 'cd ///\n echo $PWD'
assert 'cd /tmp\n echo $PWD'
assert 'cd /tmp/\n echo $PWD'
assert 'cd /tmp///\n echo $PWD'
assert 'cd /../../../././.././\n echo $PWD'
assert 'cd src\n echo $PWD'
assert 'unset HOME\ncd \n echo $PWD'

## echo
assert 'echo'
assert 'echo hello'
assert 'echo hello "    " world'
assert 'echo -n'
assert 'echo -n hello'
assert 'echo -n hello world'
assert 'echo hello -n'
assert 'echo -nn'
assert 'echo -nnn'
assert 'echo -nna'
assert 'echo -n-n-n'
assert 'echo 1nnnn'
assert 'echo ";|()"'

## pwd
assert 'pwd'
assert 'cd\npwd'
assert 'cd src\npwd'
assert 'cd /etc\npwd'
assert 'cd . \n pwd \n echo $PWD $OLDPWD'
assert 'cd .. \n pwd \n echo $PWD $OLDPWD'
assert 'cd /// \n pwd \n echo $PWD $OLDPWD'
assert 'cd /tmp/// \n pwd \n echo $PWD $OLDPWD'
assert 'unset PWD\npwd\ncd /etc\npwd'

## export attribute
print_desc 'export hoge fuga=fuga'
assert 'unset PWD \n cd \n echo $PWD \ncd /tmp\necho $PWD'
assert 'unset PWD\ncd\necho $OLDPWD\ncd /tmp\necho $OLDPWD'
assert 'unset PWD\ncd\nexport|grep PWD\ncd /tmp\nexport|grep PWD'
assert 'unset PWD\ncd\nenv|grep PWD\ncd /tmp\nenv|grep PWD'

cleanup

if [ -f error.log ]; then
	echo -e $RED"Some tests have failed. Please review the error.log for more information."$RESET
fi
