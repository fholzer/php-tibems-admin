<?php

class TibcoUsers
{
	private $users;

	function __construct()
	{
		$users = tibcoadm_getusers();
		sort($users);
		foreach($users as $user)
		{
			$this->users[] = new TibcoUser($user);
		}
	}

	public function getAll()
	{
		return $this->users;
	}
}

?>