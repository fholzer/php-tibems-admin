<?php

class TibcoGroup
{
	private $group;
	private $usercount = -1;

	function __construct($group)
	{
		$this->group = $group;
	}

	public function getName()
	{
		return $this->group['name'];
	}
	
	public function getDesc()
	{
		return $this->group['desc'];
	}

	public function getUserCount()
	{
		if($this->usercount < 0) {
			$i=0;
			while(is_array($this->group['u'.$i]))
			{
				$i++;
			}
			return $i;
		}else{
			return $usercount;
		}
	}
}

?>