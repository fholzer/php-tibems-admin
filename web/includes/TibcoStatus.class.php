<?php

class TibcoStatus
{
	private $serverinfo;

	function __construct()
	{
		$this->serverinfo = tibcoadm_getstatus();
	}

	function getServer()
	{
		return $this->serverinfo['server'];
	}
	
	function getState()
	{
		switch($this->serverinfo['state'])
		{
			case 0:
				return 'Starting up';
				break;
			case 1:
				return 'Restoring...';
				break;
			case 2:
				return 'Standby';
				break;
			case 3:
				return 'FT-Standby';
				break;
			case 4:
				return 'Active';
				break;
			case 5:
				return 'Shutdown';
				break;
		}
	}
	
	function getVersion()
	{
		return $this->serverinfo['version'];
	}
	
	function getListen()
	{
		return $this->serverinfo['listen0'];
	}
	
	function getMaxconns()
	{
		return $this->serverinfo['maxconns'];
	}
	
	function getConnnum()
	{
		return $this->serverinfo['connnum'];
	}
	
	function getQueuenum()
	{
		return $this->serverinfo['queuenum'];
	}
	
	function getTmpqueuenum()
	{
		return $this->serverinfo['tmpqnum'];
	}
	
	function getDynqueuenum()
	{
		return $this->serverinfo['dynqnum'];
	}
	
	function getTopicnum()
	{
		return $this->serverinfo['topicnum'];
	}
	
	function getTmptopicnum()
	{
		return $this->serverinfo['tmptnum'];
	}
	
	function getDyntopicnum()
	{
		return $this->serverinfo['dyntnum'];
	}
	
	function getConsnum()
	{
		return $this->serverinfo['consnum'];
	}
	
	function getSessnum()
	{
		return $this->serverinfo['sessnum'];
	}
	
	function getDurablenum()
	{
		return $this->serverinfo['durablenum'];
	}
	
	function getProdnum()
	{
		return $this->serverinfo['prodnum'];
	}
	
	function getInrm()
	{
		return $this->serverinfo['inrm'];
	}
	
	function getOutrm()
	{
		return $this->serverinfo['outrm'];
	}
	
	function getInmct()
	{
		return $this->serverinfo['inmct'];
	}
	
	function getOutmct()
	{
		return $this->serverinfo['outmct'];
	}
	
	function getPendcount()
	{
		return $this->serverinfo['pendcount'];
	}

	function getPendsize()
	{
		return bytes($this->serverinfo['pendsize']);
	}

	function getUptime()
	{
		return dateDifference($this->getStartTime(),$this->getCurrentTime());
	}

	function getStartTime()
	{
		return $this->serverinfo['stime'];
	}

	function getCurrentTime()
	{
		return $this->serverinfo['ctime'];
	}
}

?>