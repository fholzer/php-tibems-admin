<?php

class TibcoDurable
{
	private $durable;

	function __construct($durable)
	{
		$this->durable = $durable;
	}

	public function getTn()
	{
		return $this->durable['tn'];
	}

	public function getName()
	{
		return $this->durable['name'];
	}

	public function getClientID()
	{
		return $this->durable['clientID'];
	}

	public function getNm()
	{
		return $this->durable['nm'];
	}

	public function getPs()
	{
		return bytes($this->durable['ps']);
	}

	public function getCi()
	{
		return $this->durable['ci'];
	}

	public function isOnline()
	{
		return $this->durable['online'];
	}

	public function noLocal()
	{
		return $this->durable['nolocal'];
	}
}

?>