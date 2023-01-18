g++ test.cpp -o test.out
g++ cf.cpp -o cf.out
g++ lightoj.cpp -o lightoj.out
cnt=1
while true; do
	./test.out > input.txt
	./cf.out < input.txt > output.txt
	./lightoj.out < input.txt > output2.txt
	
	if [[ $(diff output.txt output2.txt) ]]
	then
		echo "Input:"
		cat ./input.txt
		echo "cf:"
		cat ./output.txt
		echo "lightoj:"
		cat ./output2.txt
		break
	fi
	echo "iteration: $cnt"
	cnt=$((cnt+1))
done