#include "ns3/command-line.h"
#include "ns3/config.h"
#include "ns3/string.h"
#include "ns3/log.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/mobility-helper.h"
#include "ns3/on-off-helper.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/mobility-model.h"
#include "ns3/packet-sink.h"
#include "ns3/packet-sink-helper.h"
#include "ns3/tcp-westwood.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/nstime.h"
#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include <cstring>
#include <cstdlib>
#include "ns3/traffic-control-module.h"
#include "ns3/flow-monitor-helper.h"
#include <bits/stdc++.h>
using namespace std;
using namespace ns3;

Ptr<PacketSink> sink;

uint64_t lastTotalRx = 0;

void CalculateThroughput ()
{
  Time now = Simulator::Now ();
  double cur = (sink->GetTotalRx () - lastTotalRx) * (double) 8 / 1e5;
  cout << now.GetSeconds () << "s: \t" << cur << " Mbit/s" << endl;
  lastTotalRx = sink->GetTotalRx ();
  Simulator::Schedule (MilliSeconds (100), &CalculateThroughput);
}

int main (int argc, char *argv[])
{
	string dataRate;
  uint32_t payloadSize = 1472;
  double simulationTime = 10;
  int user=6; // including AP
  int extraNodes=1;
  
  double speed=1; // m/s
  int countOfServerPort=1;
  double rate=1.0;

  CommandLine cmd (__FILE__);
  cmd.AddValue ("extraNodes", "Number of extra nodes", extraNodes);
  cmd.AddValue ("speed", "Speed", speed);
  cmd.AddValue ("countOfServerPort", "For flow count", countOfServerPort);
  cmd.AddValue ("rate", "Set data rate", rate);

  cmd.Parse (argc, argv);

  dataRate=to_string(rate)+"Mbps";
  int total=user+extraNodes+3;

  NodeContainer nodes;
  nodes.Create(total);
  
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName ("ns3::TcpNewReno")));
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (payloadSize));
  Config::SetDefault ("ns3::RedQueueDisc::MaxSize",
                          QueueSizeValue (QueueSize (QueueSizeUnit::PACKETS, 20)));
  Config::SetDefault ("ns3::RedQueueDisc::MinTh", DoubleValue (10));
  Config::SetDefault ("ns3::RedQueueDisc::MaxTh", DoubleValue (20));
  Config::SetDefault ("ns3::RedQueueDisc::LinkBandwidth", StringValue ("5Mbps"));
  Config::SetDefault ("ns3::RedQueueDisc::LinkDelay", StringValue ("6ms"));

  // bottleneck
  PointToPointHelper pph_bottleneck;
  pph_bottleneck.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
  pph_bottleneck.SetChannelAttribute("Delay", StringValue("6ms"));
  NetDeviceContainer d_bottleneck[extraNodes+1];
  for(int i=0;i<=extraNodes;i++)
  {
      d_bottleneck[i]=pph_bottleneck.Install(nodes.Get(user+i),nodes.Get(user+i+1));
  }

  //server
  PointToPointHelper pph_server;
  pph_server.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
  pph_server.SetChannelAttribute("Delay", StringValue("2ms"));
  NetDeviceContainer d_server;
  d_server=pph_server.Install(nodes.Get(total-2),nodes.Get(total-1));
  
  //Users
  PointToPointHelper pph_ap;
  pph_ap.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
  pph_ap.SetChannelAttribute("Delay", StringValue("2ms"));
  NetDeviceContainer d_ap;
  d_ap=pph_ap.Install(nodes.Get(0),nodes.Get(user));

  WifiMacHelper wifiMac;
  WifiHelper wifiHelper;
  wifiHelper.SetStandard (WIFI_STANDARD_80211n_5GHZ);

  /* Set up Legacy Channel */
  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (5e9));

  /* Setup Physical Layer */
  YansWifiPhyHelper wifiPhy;
  wifiPhy.SetChannel (wifiChannel.Create ());
  wifiPhy.SetErrorRateModel ("ns3::YansErrorRateModel");
  wifiHelper.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                      "DataMode", StringValue ("HtMcs7"),
                                      "ControlMode", StringValue ("HtMcs0"));

  Ptr<Node> apWifiNode = nodes.Get (0);
  NodeContainer staWifiNodes;
  for(int i=1;i<user;i++)
    staWifiNodes.Add(nodes.Get (i));

  /* Configure AP */
  Ssid ssid = Ssid ("network");
  wifiMac.SetType ("ns3::ApWifiMac",
                   "Ssid", SsidValue (ssid));

  NetDeviceContainer apDevice;
  apDevice = wifiHelper.Install (wifiPhy, wifiMac, apWifiNode);

  /* Configure STA */
  wifiMac.SetType ("ns3::StaWifiMac",
                   "Ssid", SsidValue (ssid));

  NetDeviceContainer staDevices;
  staDevices = wifiHelper.Install (wifiPhy, wifiMac, staWifiNodes);

  /* Mobility model */
  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (0.0),
                                 "MinY", DoubleValue (0.0),
                                 "DeltaX", DoubleValue (5.0),
                                 "DeltaY", DoubleValue (10.0),
                                 "GridWidth", UintegerValue (3),
                                 "LayoutType", StringValue ("RowFirst"));
  mobility.SetMobilityModel ("ns3::ConstantVelocityMobilityModel");
  mobility.Install (staWifiNodes);
	for(int i=0;i<user-1;i++)
	{
		Ptr<Node> node = staWifiNodes.Get(i);
		node->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(Vector(speed, 0, 0));
	}

  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (apWifiNode);

  /* Internet stack */
  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  
  address.SetBase ("10.0.1.0", "255.255.255.0");
  Ipv4InterfaceContainer apInterface,staInterface;
  apInterface = address.Assign (apDevice);
  staInterface = address.Assign (staDevices);

	address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer ip_ap;
  ip_ap=address.Assign (d_ap);

  address.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer ip_server;
  ip_server = address.Assign (d_server);

  for(int i=0;i<=extraNodes;i++)
  {
    string s="10.1."+to_string(i+4)+".0";
    char c[s.size()+1];
    for(int j=0;j<(int)s.size();j++)
      c[j]=s[j];
    c[s.size()]=0;
    address.SetBase(c,"255.255.255.0");
    address.Assign(d_bottleneck[i]);
  }


  /* Install TCP Receiver on the server */
  for(int i=0;i<countOfServerPort;i++)
  {
    PacketSinkHelper sinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), 9+i));
    ApplicationContainer sinkApp = sinkHelper.Install (nodes.Get(total-1));
    sink = StaticCast<PacketSink> (sinkApp.Get (0));
    sinkApp.Start (Seconds (0.0));
    sinkApp.Stop (Seconds (simulationTime));
  }
  

  /* Install TCP Transmitter on the users */
  for(int i=0;i<countOfServerPort;i++)
  {
    OnOffHelper userH ("ns3::TcpSocketFactory", (InetSocketAddress (ip_server.GetAddress (1), 9+i)));
    userH.SetAttribute ("PacketSize", UintegerValue (payloadSize));
    userH.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
    userH.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
    userH.SetAttribute ("DataRate", DataRateValue (DataRate (dataRate)));
    NodeContainer flowNodes;
    for(int i=0;i<user-1;i++)
    {
      flowNodes.Add(staWifiNodes.Get(i));
    }
    ApplicationContainer userApp = userH.Install (flowNodes);
    userApp.Start (Seconds (0.0001));
    userApp.Stop (Seconds (simulationTime));
  }
  

  Ptr<FlowMonitor> flowMonitor;
  FlowMonitorHelper flowHelper;
  flowMonitor = flowHelper.InstallAll();

  
  


  //Simulator::Schedule (Seconds (1.1), &CalculateThroughput);

  //wifiPhy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11_RADIO);
  //wifiPhy.EnablePcap ("SIM/taskA/A", apDevice);
  //wifiPhy.EnablePcap ("SIM/taskA/A", staDevices);
  //pph_ap.EnablePcapAll("SIM/taskA/A");

	/* Populate routing table */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();


  /* Start Simulation */
  Simulator::Stop (Seconds (simulationTime));
  Simulator::Run ();

  flowMonitor->SerializeToXmlFile("SIM/taskA/flowmon.xml", true, true);

  //double averageThroughput = ((sink->GetTotalRx () * 8) / (1e6 * simulationTime));
  double averageThroughput2=0;
  double totalDelay=0;
  int totalRxPackets=0;
  int totalTxPackets=0;
  int totalDroppedPackets=0;
  for(auto itr:flowMonitor->GetFlowStats())
  {
    averageThroughput2+=itr.second.rxBytes*8.0/(1e6 * simulationTime);
    totalDelay+=itr.second.delaySum.GetMilliSeconds();
    totalRxPackets+=itr.second.rxPackets;
    totalTxPackets+=itr.second.txPackets;
    totalDroppedPackets+=itr.second.lostPackets;
    
  }

  double deliveryRatio=totalRxPackets*100.0/totalTxPackets;
  double dropRatio=totalDroppedPackets*100.0/totalTxPackets;
  double averageDelay=totalDelay/totalRxPackets;


  Simulator::Destroy ();
  // cout << "\nAverage throughput: " << averageThroughput2 << " Mbit/s" << endl;
  // cout << "\nAverage delay: " << averageDelay << " ms" << endl;
  // cout << "\nDelivery Ratio: " << deliveryRatio << " %" << endl;
  // cout << "\nDrop Ratio: " << dropRatio << " %" << endl;
  // cout << "\nFlows: "<<flowMonitor->GetFlowStats().size()<<endl;

  cout<<total<<",";
  cout<<countOfServerPort*(user-1)<<",";
  cout<<rate*1e6/(payloadSize*8)<<",";
  cout<<speed<<",";
  cout<<averageThroughput2<<",";
  cout<<averageDelay<<",";
  cout<<deliveryRatio<<",";
  cout<<dropRatio<<"\n";

  return 0;
}
