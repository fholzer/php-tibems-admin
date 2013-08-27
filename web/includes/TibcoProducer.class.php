<?php

class TibcoProducer
{
	private $producer;

	function __construct($producer)
	{
		$this->producer = $producer;
	}

	function getPid()
	{
		return $this->producer['pid'];
	}

	function getConnID()
	{
		return $this->producer['connID'];
	}

	function getUn()
	{
		return $this->producer['un'];
	}

	function getDn()
	{
		return $this->producer['dn'];
	}

	function getMct()
	{
		return $this->producer['mct'];
	}

	function getMsz()
	{
		return bytes($this->producer['msz']);
	}
}

?>