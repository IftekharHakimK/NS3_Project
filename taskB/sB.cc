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
  CommandLine cmd (__FILE__);
  int user=10;
  int attacker=10;
  bool rred=false;
  bool withAttack=true;

  cmd.AddValue ("user", "Number of user nodes", user);
  cmd.AddValue ("attacker", "Number of attacker nodes", attacker);
  cmd.AddValue ("rred", "Enable RRED?", rred);
  cmd.AddValue ("withAttack", "Enable LDoS Attack?", withAttack);
  cmd.Parse (argc,argv);


  uint32_t payloadSize = 1472;
  double simulationTime = 10;

  
  int total=user+attacker+3;

  

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
  Config::SetDefault ("ns3::RedQueueDisc::RRED",BooleanValue(rred));

  // bottleneck
  PointToPointHelper pph_bottleneck;
  pph_bottleneck.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
  pph_bottleneck.SetChannelAttribute("Delay", StringValue("6ms"));
  NetDeviceContainer d_bottleneck;
  d_bottleneck=pph_bottleneck.Install(nodes.Get(total-3),nodes.Get(total-2));
  
  //server
  PointToPointHelper pph_server;
  pph_server.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
  pph_server.SetChannelAttribute("Delay", StringValue("2ms"));
  NetDeviceContainer d_server;
  d_server=pph_server.Install(nodes.Get(total-2),nodes.Get(total-1));
  
  //attacker
  PointToPointHelper pph_attacker;
  pph_attacker.SetDeviceAttribute("DataRate", StringValue("2Mbps"));
  pph_attacker.SetChannelAttribute("Delay", StringValue("2ms"));
  NetDeviceContainer d_attacker[attacker];
  for(int i=0;i<attacker;i++)
  {
    d_attacker[i]=pph_attacker.Install(nodes.Get(i),nodes.Get(total-3));
  }

  //Users
  PointToPointHelper pph_user;
  pph_user.SetDeviceAttribute("DataRate", StringValue("2Mbps"));
  pph_user.SetChannelAttribute("Delay", StringValue("2ms"));
  NetDeviceContainer d_user[user];
  for(int i=attacker;i<attacker+user;i++)
  {
    d_user[i-attacker]=pph_user.Install(nodes.Get(i),nodes.Get(total-3));
  }


  /* Internet stack */
  InternetStackHelper stack;
  stack.Install (nodes);

  TrafficControlHelper tchBottleneck;
  tchBottleneck.SetRootQueueDisc ("ns3::RedQueueDisc");
  QueueDiscContainer queueDiscs;
  queueDiscs.Add(tchBottleneck.Install (d_bottleneck.Get(0)));

  Ipv4AddressHelper address;

  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer ip_bottleneck;
  ip_bottleneck = address.Assign (d_bottleneck);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer ip_server;
  ip_server = address.Assign (d_server);

  Ipv4InterfaceContainer ip_users[user];
  for(int i=0;i<user;i++)
  {
    string s="10.1."+to_string(i+3)+".0";
    char c[s.size()+1];
    for(int j=0;j<(int)s.size();j++)
      c[j]=s[j];
    c[s.size()]=0;
    address.SetBase(c,"255.255.255.0");
    //cout<<c<<endl;
    ip_users[i]=address.Assign(d_user[i]);
  }

  Ipv4InterfaceContainer ip_attackers[attacker];
  for(int i=0;i<attacker;i++)
  {
    string s="10.1."+to_string(i+3+user)+".0";
    char c[s.size()+1];
    for(int j=0;j<(int)s.size();j++)
      c[j]=s[j];
    c[s.size()]=0;
    address.SetBase(c,"255.255.255.0");
    //cout<<c<<endl;
    ip_attackers[i]=address.Assign(d_attacker[i]);
  }

  /* Populate routing table */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  /* Install TCP Receiver on the access point */
  PacketSinkHelper sinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), 9));
  ApplicationContainer sinkApp = sinkHelper.Install (nodes.Get(total-1));
  sink = StaticCast<PacketSink> (sinkApp.Get (0));

  PacketSinkHelper UDPsink("ns3::UdpSocketFactory",
                           Address(InetSocketAddress(Ipv4Address::GetAny(), 9001)));
  ApplicationContainer UDPSinkApp = UDPsink.Install(nodes.Get(total-1));
  

  /* Install TCP Transmitter on the users */
  OnOffHelper userH ("ns3::TcpSocketFactory", (InetSocketAddress (ip_server.GetAddress (1), 9)));
  userH.SetAttribute ("PacketSize", UintegerValue (payloadSize));
  userH.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  userH.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
  userH.SetAttribute ("DataRate", DataRateValue (DataRate ("2Mbps")));
  
  NodeContainer userNodes;
  for(int i=attacker;i<attacker+user;i++)
    userNodes.Add(nodes.Get(i));
  ApplicationContainer userApp = userH.Install (userNodes);

  

  OnOffHelper attackerH("ns3::UdpSocketFactory",
                    Address(InetSocketAddress(ip_server.GetAddress(1), 9001)));
  attackerH.SetConstantRate(DataRate((string)"2Mbps"));
  attackerH.SetAttribute("OnTime", StringValue("ns3::ConstantRandomVariable[Constant=" + (string)"0.6" + "]"));
  attackerH.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=" + (string)"0.4" + "]"));
  NodeContainer attackerNodes;
  for(int i=0;i<attacker;i++)
  {
    attackerNodes.Add(nodes.Get(i));
  }
  ApplicationContainer attackerApp;
  if(withAttack)
    attackerApp = attackerH.Install(attackerNodes);
  

  sinkApp.Start (Seconds (0.0));
  UDPSinkApp.Start(Seconds(0.0));
  userApp.Start (Seconds (0.0));
  if(withAttack)
    attackerApp.Start(Seconds(0.0));
  

  Ptr<FlowMonitor> flowMonitor;
  FlowMonitorHelper flowHelper;
  flowMonitor = flowHelper.InstallAll();

  sinkApp.Stop (Seconds (simulationTime));
  UDPSinkApp.Stop(Seconds(simulationTime));
  userApp.Stop (Seconds (simulationTime));
  if(withAttack)
    attackerApp.Stop(Seconds(simulationTime));


  //Simulator::Schedule (Seconds (1.1), &CalculateThroughput);

  //pph_server.EnablePcapAll("SIM/taskB");

  /* Start Simulation */
  Simulator::Stop (Seconds (simulationTime));
  Simulator::Run ();

  flowMonitor->SerializeToXmlFile("SIM/taskB/flowmon.xml", true, true);

  double averageThroughput = ((sink->GetTotalRx () * 8) / (1e6 * simulationTime));
  //cout<<queueDiscs.Get (0)->GetStats ()<<endl;

  int totalTxPackets=0;
  int totalLostPackets=0;
  auto itr=flowMonitor->GetFlowStats().begin();
  for(int i=0;i<user;i++)
  {
    totalLostPackets+=itr->second.lostPackets;
    totalTxPackets+=itr->second.txPackets;
  }
  double dropRatio=totalLostPackets*100.0/totalTxPackets;
  Simulator::Destroy ();
  //cout << "\nAverage throughput: " << averageThroughput << " Mbit/s" << endl;
  //cout << "\nDrop Ratio: " << dropRatio << " %" << endl;

  cout<<attacker<<",";
  cout<<averageThroughput<<",";
  cout<<dropRatio<<"\n";

  return 0;
}
