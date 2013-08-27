<?php

class TibcoConnection
{
	private $connection;

	function __construct($connection)
	{
		$this->connection = $connection;
	}

	public function getCltype()
	{
		return $this->connection['cltype'];
	}
	
	public function getConnID()
	{
		return $this->connection['connID'];
	}
	
	public function getClientID()
	{
		return $this->connection['clientID'];
	}
	
	public function getHost()
	{
		return $this->connection['host'];
	}
	
	public function getIpaddr()
	{
		return $this->connection['ipaddr'];
	}
	
	public function getUserName()
	{
		return $this->connection['userName'];
	}

	public function getCs()
	{
		return $this->connection['cs'];
	}

	public function isStarted()
	{
		return $this->connection['started'];
	}

	public function isAdmin()
	{
		return $this->connection['admin'];
	}

	public function isXa()
	{
		return $this->connection['xa'];
	}

	public function isFt()
	{
		return $this->connection['ft'];
	}

	public function isSSL()
	{
		return $this->connection['ssl'];
	}

	public function getConnType()
	{
		return $this->connection['connType'];
	}

	function getUptime()
	{
		return dateDifference($this->getStartTime(),$this->getCurrentTime());
	}

	function getStartTime()
	{
		return $this->connection['stime'];
	}

	function getCurrentTime()
	{
		return $this->connection['ctime'];
	}

	public function getFlags()
	{
		$flags = '';
		if($this->isFt())
			$flags .= '+';
		else
			$flags .= '-';
		if($this->isSSL())
			$flags .= '+';
		else
			$flags .= '-';
		if($this->isXa())
			$flags .= '+';
		else
			$flags .= '-';
		if($this->isAdmin())
			$flags .= 'A';
		else
		switch($this->connection['connType'])
		{
			case 'CONNECTION':
				$flags .= 'C';
				break;
			case 'TOPIC':
				$flags .= 'T';
				break;
			case 'ROUTE':
				$flags .= 'R';
				break;
			case 'FT':
				$flags .= 'F';
				break;
			case 'QUEUE':
				$flags .= 'Q';
				break;
			default:
				$flags .= '-';
				break;
		}
		return $flags;
	}
}

?>