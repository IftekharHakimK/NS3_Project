echo "#Attacker,Throughput,Drop Ratio (%)" > SIM/taskB/varyAttackerNodesWithoutRRED.csv
./waf --run "scratch/sB --user=10 --attacker=2 --rred=false --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithoutRRED.csv
./waf --run "scratch/sB --user=10 --attacker=4 --rred=false --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithoutRRED.csv
./waf --run "scratch/sB --user=10 --attacker=8 --rred=false --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithoutRRED.csv
./waf --run "scratch/sB --user=10 --attacker=12 --rred=false --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithoutRRED.csv
./waf --run "scratch/sB --user=10 --attacker=16 --rred=false --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithoutRRED.csv
./waf --run "scratch/sB --user=10 --attacker=20 --rred=false --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithoutRRED.csv
./waf --run "scratch/sB --user=10 --attacker=30 --rred=false --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithoutRRED.csv
./waf --run "scratch/sB --user=10 --attacker=50 --rred=false --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithoutRRED.csv

echo "#Attacker,Throughput,Drop Ratio (%)" > SIM/taskB/varyAttackerNodesWithRRED.csv
./waf --run "scratch/sB --user=10 --attacker=2 --rred=true --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithRRED.csv
./waf --run "scratch/sB --user=10 --attacker=4 --rred=true --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithRRED.csv
./waf --run "scratch/sB --user=10 --attacker=8 --rred=true --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithRRED.csv
./waf --run "scratch/sB --user=10 --attacker=12 --rred=true --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithRRED.csv
./waf --run "scratch/sB --user=10 --attacker=16 --rred=true --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithRRED.csv
./waf --run "scratch/sB --user=10 --attacker=20 --rred=true --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithRRED.csv
./waf --run "scratch/sB --user=10 --attacker=30 --rred=true --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithRRED.csv
./waf --run "scratch/sB --user=10 --attacker=50 --rred=true --withAttack=true"|tail -1 >> SIM/taskB/varyAttackerNodesWithRRED.csv

