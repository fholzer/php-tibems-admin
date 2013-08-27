<?php

class TibcoPermissions
{
	private $permissions;

	function __construct($uname)
	{
		$permissions = tibcoadm_getpermissions($uname);
		$i=0;
		while(is_array($permissions['a'.$i]))
		{
			$this->permissions[] = new TibcoPermission($permissions['a'.$i]);
			$i++;
		}
	}

	function getAll()
	{
		return $this->permissions;
	}
}

?>