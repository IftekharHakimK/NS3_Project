echo "Nodes,Flows,Packet/s,Speed,Throughput,Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA/varyNodes.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyNodes.csv
./waf --run "scratch/sA1 --extraNodes=1 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyNodes.csv
./waf --run "scratch/sA1 --extraNodes=2 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyNodes.csv
./waf --run "scratch/sA1 --extraNodes=5 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyNodes.csv
./waf --run "scratch/sA1 --extraNodes=10 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyNodes.csv
./waf --run "scratch/sA1 --extraNodes=20 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyNodes.csv

echo "Nodes,Flows,Packet/s,Speed,Throughput,Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA/varyFlows.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyFlows.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=2 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyFlows.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=3 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyFlows.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=4 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyFlows.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=5 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyFlows.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=6 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyFlows.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=7 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyFlows.csv

echo "Nodes,Flows,Packet/s,Speed,Throughput,Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA/varyPps.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=0.2"|tail -1 >> SIM/taskA/varyPps.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=0.4"|tail -1 >> SIM/taskA/varyPps.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=0.6"|tail -1 >> SIM/taskA/varyPps.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=0.8"|tail -1 >> SIM/taskA/varyPps.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=1"|tail -1 >> SIM/taskA/varyPps.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=2"|tail -1 >> SIM/taskA/varyPps.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=3"|tail -1 >> SIM/taskA/varyPps.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=4"|tail -1 >> SIM/taskA/varyPps.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=1 --rate=5"|tail -1 >> SIM/taskA/varyPps.csv

echo "Nodes,Flows,Packet/s,Speed,Throughput,Delay(ms),Delivery Ratio(%),Drop Ratio (%)" > SIM/taskA/varySpeed.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=10 --rate=1"|tail -1 >> SIM/taskA/varySpeed.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=20 --rate=1"|tail -1 >> SIM/taskA/varySpeed.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=30 --rate=1"|tail -1 >> SIM/taskA/varySpeed.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=40 --rate=1"|tail -1 >> SIM/taskA/varySpeed.csv
./waf --run "scratch/sA1 --extraNodes=0 --countOfServerPort=1 --speed=50 --rate=1"|tail -1 >> SIM/taskA/varySpeed.csv
