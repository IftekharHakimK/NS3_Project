set datafile separator ","
set terminal png 
#Varying Nodes
set xlabel "Nodes"
set output "varyNodes/Throughput.png"
set title "Nodes vs Throughput"
set ylabel "Throughput(Kbps)"
plot "varyNodes.csv" using 1:5 with lines title "plot"

set output "varyNodes/Delay.png"
set title "Nodes vs Delay(ms)"
set ylabel "Delay(ms)"
plot "varyNodes.csv" using 1:6 with lines title "plot"

set output "varyNodes/DeliveryRatio.png"
set title "Nodes vs DeliveryRatio"
set ylabel "DeliveryRatio(%)"
plot "varyNodes.csv" using 1:7 with lines title "plot"

set output "varyNodes/DropRatio.png"
set title "Nodes vs DropRatio"
set ylabel "DropRatio(%)"
plot "varyNodes.csv" using 1:8 with lines title "plot"

#Varying Flows
set xlabel "Flows"
set output "varyFlows/Throughput.png"
set title "Flows vs Throughput"
set ylabel "Throughput(Kbps)"
plot "varyFlows.csv" using 2:5 with lines title "plot"

set output "varyFlows/Delay.png"
set title "Flows vs Delay(ms)"
set ylabel "Delay(ms)"
plot "varyFlows.csv" using 2:6 with lines title "plot"

set output "varyFlows/DeliveryRatio.png"
set title "Flows vs DeliveryRatio"
set ylabel "DeliveryRatio(%)"
plot "varyFlows.csv" using 2:7 with lines title "plot"

set output "varyFlows/DropRatio.png"
set title "Flows vs DropRatio"
set ylabel "DropRatio(%)"
plot "varyFlows.csv" using 2:8 with lines title "plot"

#Varying Pps
set xlabel "Pps"
set output "varyPps/Throughput.png"
set title "Pps vs Throughput(Kbps)"
set ylabel "Throughput"
plot "varyPps.csv" using 3:5 with lines title "plot"

set output "varyPps/Delay.png"
set title "Pps vs Delay(ms)"
set ylabel "Delay(ms)"
plot "varyPps.csv" using 3:6 with lines title "plot"

set output "varyPps/DeliveryRatio.png"
set title "Pps vs DeliveryRatio"
set ylabel "DeliveryRatio(%)"
plot "varyPps.csv" using 3:7 with lines title "plot"

set output "varyPps/DropRatio.png"
set title "Pps vs DropRatio"
set ylabel "DropRatio(%)"
plot "varyPps.csv" using 3:8 with lines title "plot"

#Varying Speed
set xlabel "Speed"
set output "varySpeed/Throughput.png"
set title "Speed vs Throughput"
set ylabel "Throughput(Kbps)"
plot "varySpeed.csv" using 4:5 with lines title "plot"

set output "varySpeed/Delay.png"
set title "Speed vs Delay(ms)"
set ylabel "Delay(ms)"
plot "varySpeed.csv" using 4:6 with lines title "plot"

set output "varySpeed/DeliveryRatio.png"
set title "Speed vs DeliveryRatio"
set ylabel "DeliveryRatio(%)"
plot "varySpeed.csv" using 4:7 with lines title "plot"

set output "varySpeed/DropRatio.png"
set title "Speed vs DropRatio"
set ylabel "DropRatio(%)"
plot "varySpeed.csv" using 4:8 with lines title "plot"

