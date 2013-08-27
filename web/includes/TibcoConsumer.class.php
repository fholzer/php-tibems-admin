<?php

class TibcoConsumer
{
	private $consumer;

	function __construct($consumer)
	{
		$this->consumer = $consumer;
	}

	function getCid()
	{
		return $this->consumer['cid'];
	}

	function getConnID()
	{
		return $this->consumer['connID'];
	}

	function getUn()
	{
		return $this->consumer['un'];
	}

	function getDn()
	{
		return $this->consumer['dn'];
	}

	function getMct()
	{
		return $this->consumer['mct'];
	}

	function getMsz()
	{
		return bytes($this->consumer['msz']);
	}

	function getUptime()
	{
		return dateDifference(0,$this->consumer['upt']);
	}
}

?>