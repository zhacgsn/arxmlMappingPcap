arxmlMappingPcap
=========
如何运行
------
cmake .
make
./xmltest
### 运行结果
HEADER-ID 103---->PDU: VolumeRequest
HEADER-ID 65536100---->PDU: VehicleSpeed
HEADER-ID 65536101---->PDU: VehicleDistance
HEADER-ID 65601636---->PDU: EMotorStatus
HEADER-ID 65667172---->PDU: BatteryStatus
HEADER-ID 65732708---->PDU: Time
HEADER-ID 65732709---->PDU: ExteriorTemperature
HEADER-ID 131072100---->PDU: TrafficSignInfoPDU
HEADER-ID 131072101---->PDU: LaneInfoPDU
HEADER-ID 131137636---->PDU: TrafficSignDetectionPDU
HEADER-ID 131137637---->PDU: LaneDetectionPDU
HEADER-ID 131203172---->PDU: ObstacleDetectionPDU

PDU ADAS_UDP_NM has signal: 
	RepeatMessageRequest at index 0
	NMCoordinatorSleeptReadyBit at index 3
	ActiveWakeupBit at index 4
	PartialNetworkInformationBit at index 6
	NodeId at index 8
	PNCVector at index 16
PDU AMP_UDP_NM has signal: 
	RepeatMessageRequest at index 0
	NMCoordinatorSleeptReadyBit at index 3
	ActiveWakeupBit at index 4
	PartialNetworkInformationBit at index 6
	NodeId at index 8
	PNCVector at index 16
PDU BatteryStatus has signal: 
	BatteryTemperature at index 0
	RemainingCapacity at index 16
	Capacity at index 48
PDU CAMF_UDP_NM has signal: 
	RepeatMessageRequest at index 0
	NMCoordinatorSleeptReadyBit at index 3
	ActiveWakeupBit at index 4
	PartialNetworkInformationBit at index 6
	NodeId at index 8
	PNCVector at index 16
PDU EMotorStatus has signal: 
	EMotorSpeed at index 0
	EMotorTemperature at index 16
	EMotorCurrent at index 32
	EMotorPower at index 64
PDU ExteriorTemperature has signal: 
	ExteriorTemperature at index 0
PDU HU_UDP_NM has signal: 
	RepeatMessageRequest at index 0
	NMCoordinatorSleeptReadyBit at index 3
	ActiveWakeupBit at index 4
	PartialNetworkInformationBit at index 6
	NodeId at index 8
	PNCVector at index 16
PDU IC_UDP_NM has signal: 
	RepeatMessageRequest at index 0
	NMCoordinatorSleeptReadyBit at index 3
	ActiveWakeupBit at index 4
	PartialNetworkInformationBit at index 6
	NodeId at index 8
	PNCVector at index 16
PDU LRR_UDP_NM has signal: 
	RepeatMessageRequest at index 0
	NMCoordinatorSleeptReadyBit at index 3
	ActiveWakeupBit at index 4
	PartialNetworkInformationBit at index 6
	NodeId at index 8
	PNCVector at index 16
PDU LaneDetectionPDU has signal: 
	LaneDetectionSerialized at index 0
PDU LaneInfoPDU has signal: 
	LaneInfoSerialized at index 0
PDU ObstacleDetectionPDU has signal: 
	ObstacleDetectionPDUSerialized at index 0
PDU Time has signal: 
	Hour at index 0
	Minute at index 8
	Second at index 16
PDU TrafficSignDetectionPDU has signal: 
	TrafficSignDetectionSerialized at index 0
PDU TrafficSignInfoPDU has signal: 
	TrafficSignInfoSerialized at index 0
PDU VGW_UDP_NM has signal: 
	RepeatMessageRequest at index 0
	NMCoordinatorSleeptReadyBit at index 3
	ActiveWakeupBit at index 4
	PartialNetworkInformationBit at index 6
	NodeId at index 8
	PNCVector at index 16
PDU VehicleDistance has signal: 
	VehicleTripDistance at index 0
	VehicleTotalDistance at index 32
PDU VehicleSpeed has signal: 
	VehicleSpeed at index 0
	VehicleDirection at index 16
PDU VolumeRequest has signal: 
	VolumeRequest at index 0

signal ActiveWakeupBit has length: 1
signal BatteryTemperature has length: 16
signal Capacity has length: 32
signal EMotorCurrent has length: 32
signal EMotorPower has length: 32
signal EMotorSpeed has length: 16
signal EMotorTemperature has length: 16
signal ExteriorTemperature has length: 16
signal Hour has length: 8
signal Minute has length: 8
signal NMCoordinatorSleeptReadyBit has length: 1
signal NodeId has length: 8
signal PNCVector has length: 16
signal PartialNetworkInformationBit has length: 1
signal RemainingCapacity has length: 32
signal RepeatMessageRequest has length: 1
signal Second has length: 8
signal VehicleDirection has length: 8
signal VehicleSpeed has length: 16
signal VehicleTotalDistance has length: 32
signal VehicleTripDistance has length: 32
signal VolumeRequest has length: 8


	<element> Hello,  World</element>

The leading space before the "Hello" and the double space after the comma are
preserved. Line-feeds are preserved, as in this example:
