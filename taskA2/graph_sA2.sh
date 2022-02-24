#echo "Nodes,Flows,Packet/s,Speed(m/s),Throughput(Kbps),Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.001" | tail -1 > SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --user=15 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.001" | tail -1 >> SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --user=25 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.001" | tail -1 >> SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --user=35 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.001" | tail -1 >> SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --user=45 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.001" | tail -1 >> SIM/taskA2/varyNodes.csv

#echo "Nodes,Flows,Packet/s,Speed(m/s),Throughput(Kbps),Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.001" | tail -1 > SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=2 --rate=0.001" | tail -1 >> SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=3 --rate=0.001" | tail -1 >> SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=4 --rate=0.001" | tail -1 >> SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=5 --rate=0.001" | tail -1 >> SIM/taskA2/varyFlows.csv

#echo "Nodes,Flows,Packet/s,Speed(m/s),Throughput(Kbps),Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.001" | tail -1 > SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.005" | tail -1 >> SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.008" | tail -1 >> SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.01" | tail -1 >> SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.02" | tail -1 >> SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=0.01 --countOfServerPort=1 --rate=0.05" | tail -1 >> SIM/taskA2/varyPps.csv

#echo "Nodes,Flows,Packet/s,Speed(m/s),Throughput(Kbps),Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=2 --countOfServerPort=1 --rate=0.001" | tail -1 > SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=5 --countOfServerPort=1 --rate=0.001" | tail -1 >> SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=10 --countOfServerPort=1 --rate=0.001" | tail -1 >> SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=20 --countOfServerPort=1 --rate=0.001" | tail -1 >> SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=30 --countOfServerPort=1 --rate=0.001" | tail -1 >> SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --user=5 --countSource=4 --speed=40 --countOfServerPort=1 --rate=0.001" | tail -1 >> SIM/taskA2/varySpeed.csv

