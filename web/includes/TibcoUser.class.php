<?php

class TibcoUser
{
	private $user;

	function __construct($user)
	{
		$this->user = $user;
	}

	public function getName()
	{
		return $this->user['name'];
	}
	
	public function getDesc()
	{
		return $this->user['desc'];
	}
}

?>