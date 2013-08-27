<?php

class TibcoBridge
{
	private $bridge;

	function __construct($bridge)
	{
		$this->bridge = $bridge;
	}

	public function getDn()
	{
		return $this->bridge['dn'];
	}

	public function getDt()
	{
		return $this->bridge['dt'];
	}

	public function getTc()
	{
		return $this->bridge['tc'];
	}

	public function getQc()
	{
		return $this->bridge['qc'];
	}
}

?>