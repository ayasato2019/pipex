make re
touch file1
chmod 775 file1

#test 1
< file1 cat | wc > cmp
./pipex file1 cat wc out
echo "test 1 cat  wc"
diff -U 3 cmp out && echo "OK\n" || echo "KO\n"

#test 2
< file1 ls | wc -l > cmp
./pipex file1 ls "wc -l" out
echo "test 2 ls wc -l"
diff -U 3 cmp out && echo "OK\n" || echo "KO\n"

#test 3
< file1 grep a | wc -m > cmp
./pipex file1 "grep a" "wc -m" out
echo "test 3 grep a wc -m"
diff -U 3 cmp out && echo "OK\n" || echo "KO\n"

#test 4
< file1 ls -a | wc -m > cmp
./pipex file1 "ls -a" "wc -m" out
echo "test 4 ls -a wc -m"
diff -U 3 cmp out && echo "OK\n" || echo "KO\n"

#test 5
echo aaa >file1
< file1 wc -l | wc -m > cmp
./pipex file1 "wc -l" "wc -m" out
echo "test 5 wc -l wc -m"
diff -U 3 cmp out && echo "OK\n" || echo "KO\n"

#test 6
echo bbb >>file1
< file1 wc -l | wc -m > cmp
./pipex file1 "wc -l" "wc -m" out
echo "test 6 wc -l wc -m"
diff -U 3 cmp out && echo "OK\n" || echo "KO\n"

#test 7
echo CCC >>file1
echo DDD >>file1
echo EEEEEE >>file1
echo F >>file1
< file1 ls | wc -l > cmp
./pipex file1 ls "wc -l" out
echo "test 6 wc -l wc -m"
diff -U 3 cmp out && echo "OK\n" || echo "KO\n"

#test 8
< file1 grep a | wc -m > cmp
./pipex file1 "grep a" "wc -m" out
echo "test 8 grep a wc -m"
diff -U 3 cmp out && echo "OK\n" || echo "KO\n"

#test 9
< file1 ls | wc -m > cmp
./pipex file1 ls "wc -m" out
echo "test 9 lst echo"
diff -U 3 cmp out && echo "OK\n" || echo "KO\n"

test 10
ruby -e 'puts "a" * 100000' > file1
< file1 cat | cat > cmp
./pipex file1 cat cat out
echo "test 10 puts "a" * 100000"
diff -U 3 cmp out && echo "OK\n" || echo "KO\n"