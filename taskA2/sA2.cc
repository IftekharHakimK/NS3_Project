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
#include "ns3/spectrum-module.h"
#include "ns3/propagation-module.h"
#include "ns3/sixlowpan-module.h"
#include "ns3/lr-wpan-module.h"
#include "ns3/ipv6-flow-classifier.h"
#include <ns3/lr-wpan-error-model.h>
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
  uint32_t payloadSize = 128;
  double simulationTime = 100;
  int user=5;
  int extraNodes=0;
  
  double speed=1;
  int countOfServerPort=1;
  double rate=2.0;

  CommandLine cmd (__FILE__);
  cmd.AddValue ("extraNodes", "Number of extra nodes", extraNodes);
  cmd.AddValue ("speed", "Speed", speed);
  cmd.AddValue ("countOfServerPort", "For flow count", countOfServerPort);
  cmd.AddValue ("rate", "Set data rate", rate);

  cmd.Parse (argc, argv);

  dataRate=to_string(rate)+"Mbps";
  //cout<<dataRate<<endl;
  int total=user+extraNodes+3;
  

  NodeContainer nodes;
  nodes.Create(total);
  NodeContainer wsnNodes;
  for(int i=0;i<user;i++)
  {
    wsnNodes.Add(nodes.Get(i));
  }
  MobilityHelper mobility;
  mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                                 "MinX", DoubleValue (0.0),
                                 "MinY", DoubleValue (0.0),
                                 "DeltaX", DoubleValue (5.0),
                                 "DeltaY", DoubleValue (10.0),
                                 "GridWidth", UintegerValue (3),
                                 "LayoutType", StringValue ("RowFirst"));
  mobility.SetMobilityModel ("ns3::ConstantVelocityMobilityModel");
  mobility.Install (wsnNodes);
	for(int i=0;i<user-1;i++)
	{
		Ptr<Node> node = wsnNodes.Get(i);
		node->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(Vector(speed, 0, 0));
	}
  LrWpanHelper lrWpanHelper;
  NetDeviceContainer lrwpanDevices = lrWpanHelper.Install (wsnNodes);
  lrWpanHelper.AssociateToPan (lrwpanDevices, 0);
  InternetStackHelper internetv6;
  internetv6.Install(nodes);
  SixLowPanHelper sixLowPanHelper;
  NetDeviceContainer sixLowPanDevices = sixLowPanHelper.Install (lrwpanDevices);

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

  Ipv6AddressHelper ipv6;
  ipv6.SetBase (Ipv6Address ("2001:0001::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer wsnDeviceInterfaces;
  wsnDeviceInterfaces = ipv6.Assign (sixLowPanDevices);
  wsnDeviceInterfaces.SetForwarding (0, true);
  wsnDeviceInterfaces.SetDefaultRouteInAllNodes (0);

  ipv6.SetBase (Ipv6Address ("2001:0002::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer ip_server;
  ip_server = ipv6.Assign (d_server);
  ip_server.SetForwarding (1, true);
  ip_server.SetDefaultRouteInAllNodes (1);
  ip_server.SetForwarding (0, true);
  ip_server.SetDefaultRouteInAllNodes (0);

  ipv6.SetBase (Ipv6Address ("2001:0003::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer ip_ap;
  ip_ap = ipv6.Assign (d_ap);
  ip_ap.SetForwarding (1, true);
  ip_ap.SetDefaultRouteInAllNodes (1);
  ip_ap.SetForwarding (0, true);
  ip_ap.SetDefaultRouteInAllNodes (0);
  
  for(int i=0;i<=extraNodes;i++)
  {
    string s=to_string(i+4);
    while(s.size()<4) s="0"+s;
    s="2001:"+s+"::";
    char c[s.size()+1];
    for(int j=0;j<(int)s.size();j++)
      c[j]=s[j];
    c[s.size()]=0;
    ipv6.SetBase(c,Ipv6Prefix (64));
    Ipv6InterfaceContainer temp=ipv6.Assign(d_bottleneck[i]);
    temp.SetForwarding(1,true);
    temp.SetDefaultRouteInAllNodes(1);
    temp.SetDefaultRoute(0,true);
    temp.SetDefaultRouteInAllNodes(0);
  }

  for (uint32_t i = 0; i < sixLowPanDevices.GetN (); i++) 
  {
    Ptr<NetDevice> dev = sixLowPanDevices.Get (i);
    dev->SetAttribute ("UseMeshUnder", BooleanValue (true));
    dev->SetAttribute ("MeshUnderRadius", UintegerValue (10));
  }

  /* Install TCP Receiver on the server */
  for(int i=0;i<countOfServerPort;i++)
  {
    PacketSinkHelper sinkHelper ("ns3::TcpSocketFactory", Inet6SocketAddress (Ipv6Address::GetAny (), 9+i));
    sinkHelper.SetAttribute ("Protocol", TypeIdValue (TcpSocketFactory::GetTypeId ()));
    ApplicationContainer sinkApp = sinkHelper.Install (nodes.Get(total-1));
    sink = StaticCast<PacketSink> (sinkApp.Get (0));
    sinkApp.Start (Seconds (0.0));
    sinkApp.Stop (Seconds (simulationTime));
  }
  

  /* Install TCP Transmitter on the users */
  for(int i=0;i<countOfServerPort;i++)
  {
    OnOffHelper userH  ("ns3::TcpSocketFactory",
                              Inet6SocketAddress (ip_server.GetAddress (1, 1), 
                              9+i));
    //cout<<ip_server.GetAddress(1,1)<<endl;
    userH.SetAttribute ("PacketSize", UintegerValue (payloadSize));
    userH.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=10]"));
    userH.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
    userH.SetAttribute ("DataRate", DataRateValue (DataRate (dataRate)));
    //cout<<dataRate<<endl;
    NodeContainer flowNodes;
    for(int i=0;i<user;i++)
    {
      flowNodes.Add(nodes.Get(i));
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
  //wifiPhy.EnablePcap ("SIM/taskA2/A", apDevice);
  //wifiPhy.EnablePcap ("SIM/taskA2/A", staDevices);
  //pph_ap.EnablePcapAll("SIM/taskA2/A");

  /* Start Simulation */
  Simulator::Stop (Seconds (simulationTime));
  Simulator::Run ();

  //flowMonitor->SerializeToXmlFile("SIM/taskA2/flowmon.xml", true, true);

  //double averageThroughput = ((sink->GetTotalRx () * 8) / (1e3 * simulationTime));
  double averageThroughput2=0;
  double totalDelay=0;
  int totalRxPackets=0;
  int totalTxPackets=0;
  int totalDroppedPackets=0;
  for(auto itr:flowMonitor->GetFlowStats())
  {
    averageThroughput2+=itr.second.rxBytes*8.0/(1e3 * simulationTime);
    totalDelay+=itr.second.delaySum.GetMilliSeconds();
    totalRxPackets+=itr.second.rxPackets;
    totalTxPackets+=itr.second.txPackets;
    totalDroppedPackets+=itr.second.lostPackets;
    
  }

  double deliveryRatio=totalRxPackets*100.0/totalTxPackets;
  double dropRatio=totalDroppedPackets*100.0/totalTxPackets;
  double averageDelay=totalDelay/totalRxPackets;


  Simulator::Destroy ();
  //cout << fixed<<setprecision(15)<<"\nAverage throughput: " << averageThroughput << " kbit/s" << endl
  // cout << fixed<<setprecision(15)<<"\nAverage throughput: " << averageThroughput2 << " kbit/s" << endl;
  // cout << "\nAverage delay: " << averageDelay << " ms" << endl;
  // cout << "\nDelivery Ratio: " << deliveryRatio << " %" << endl;
  // cout << "\nDrop Ratio: " << dropRatio << " %" << endl;

  cout<<total<<",";
  cout<<countOfServerPort*user<<",";
  cout<<rate*1e6/payloadSize<<",";
  cout<<speed<<",";
  cout<<averageThroughput2<<",";
  cout<<averageDelay<<",";
  cout<<deliveryRatio<<",";
  cout<<dropRatio<<"\n";

  return 0;
}
