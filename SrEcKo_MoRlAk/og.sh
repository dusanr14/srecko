gpio -g mode 20 in
while true
do
	gpio -g read 20
	sleep 1
done
