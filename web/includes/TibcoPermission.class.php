<?php

class TibcoPermission
{
	private $permission;

	function __construct($permission)
	{
		$this->permission = $permission;
	}

	public function getType()
	{
		return $this->permission['acltar'];
	}

	public function hasSend()
	{
		return ($this->permission['perms'] & 1) != 0;
	}

	public function hasReceive()
	{
		return ($this->permission['perms'] & 2) != 0;
	}

	public function hasBrowse()
	{
		return ($this->permission['perms'] & 4) != 0;
	}

	public function hasPublish()
	{
		return ($this->permission['perms'] & 16) != 0;
	}

	public function hasSubscribe()
	{
		return ($this->permission['perms'] & 32) != 0;
	}

	public function hasDurable()
	{
		return ($this->permission['perms'] & 64) != 0;
	}

	public function hasUseDurable()
	{
		return ($this->permission['perms'] & 128) != 0;
	}

	public function hasView()
	{
		return ($this->permission['perms'] & 0x10000) != 0;
	}

	public function hasCreate()
	{
		return ($this->permission['perms'] & 0x20000) != 0;
	}

	public function hasModify()
	{
		return ($this->permission['perms'] & 0x80000) != 0;
	}

	public function hasDelete()
	{
		return ($this->permission['perms'] & 0x40000) != 0;
	}

	public function hasPurge()
	{
		return ($this->permission['perms'] & 0x1000000) != 0;
	}

	public function getTargetType()
	{
		switch($this->permission['acltar'])
		{
			case 1: return 'Topic';
			break;
			case 2: return 'Queue';
			break;
			case 3: return 'Admin';
			break;
			default: return 'None';
		}
	}

	public function getTargetName()
	{
		if($this->permission['acltar'] < 3)
		{
			return $this->permission['dest']['dn'];
		}else{
			return 'Admin';
		}
	}

	public function getPermissions()
	{
		$permstring = '';
		if($this->hasSend()) $permstring .= 'send,';
		if($this->hasReceive()) $permstring .= 'receive,';
		if($this->hasBrowse()) $permstring .= 'browse,';
		if($this->hasPublish()) $permstring .= 'publish,';
		if($this->hasSubscribe()) $permstring .= 'subscribe,';
		if($this->hasDurable()) $permstring .= 'durable,';
		if($this->hasUseDurable()) $permstring .= 'use durable,';
		if($this->hasView()) $permstring .= 'view,';
		if($this->hasCreate()) $permstring .= 'create,';
		if($this->hasModify()) $permstring .= 'modify,';
		if($this->hasDelete()) $permstring .= 'delete,';
		if($this->hasPurge()) $permstring .= 'purge,';

		if(strlen($permstring) > 1) {
			$permstring = substr($permstring, 0, -1);
		}
		return $permstring;
	}
}

?>