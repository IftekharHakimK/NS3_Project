echo "Nodes,Flows,Packet/s,Speed(m/s),Throughput(Kbps),Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --extraNodes=1 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --extraNodes=2 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --extraNodes=5 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --extraNodes=10 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --extraNodes=20 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyNodes.csv
./waf --run "scratch/sA2 --extraNodes=50 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyNodes.csv

echo "Nodes,Flows,Packet/s,Speed(m/s),Throughput(Kbps),Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=2 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=3 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=4 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=5 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=6 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=7 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyFlows.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=8 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varyFlows.csv

echo "Nodes,Flows,Packet/s,Speed(m/s),Throughput(Kbps),Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=0.01 --rate=0.1"|tail -1 >> SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=0.01 --rate=0.2"|tail -1 >> SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=0.01 --rate=1"|tail -1 >> SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=0.01 --rate=3"|tail -1 >> SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=0.01 --rate=5"|tail -1 >> SIM/taskA2/varyPps.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=0.01 --rate=10"|tail -1 >> SIM/taskA2/varyPps.csv

echo "Nodes,Flows,Packet/s,Speed(m/s),Throughput(Kbps),Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=2 --rate=1"|tail -1 >> SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=4 --rate=1"|tail -1 >> SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=6 --rate=1"|tail -1 >> SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=10 --rate=1"|tail -1 >> SIM/taskA2/varySpeed.csv
./waf --run "scratch/sA2 --extraNodes=0 --countOfServerPort=1 --speed=12 --rate=1"|tail -1 >> SIM/taskA2/varySpeed.csv
