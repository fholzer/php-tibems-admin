<?php

class TibcoGroups
{
	private $groups;

	function __construct()
	{
		$groups = tibcoadm_getgroups();
		sort($groups);
		foreach($groups as $group)
		{
			$this->groups[] = new TibcoGroup($group);
		}
	}

	public function getAll()
	{
		return $this->groups;
	}

	public function getGroup($name)
	{
		$data = tibcoadm_getgroup($name);
		$i=0;
		while(is_array($data['u'.$i]))
		{
			$members[] = $data['u'.$i];
			$i++;
		}
		return $members;
	}
}

?>