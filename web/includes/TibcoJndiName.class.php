<?php

class TibcoJndiName
{
	private $jndiname;

	function __construct($jndiname)
	{
		$this->jndiname = $jndiname;
	}

	function getAlias()
	{
		return $this->jndiname['alias'];
	}

	function getObjInfo()
	{
		switch($this->jndiname['at'])
		{
			case 4:
				return $this->jndiname['obj']['url'];
			break;
			case 1:
				return $this->jndiname['obj']['dn'];
			break;
		}
		return false;
	}

	function getJndiType()
	{
		switch($this->jndiname['at'])
		{
			case 4:
				switch($this->jndiname['obj']['ft'])
				{
					case 2:
						return 'TCF';
					break;
					case 1:
						return 'QCF';
					break;
					default:
						return 'CF';
				}
			break;
			case 1:
				switch($this->jndiname['obj']['dt'])
				{
					case 2:
						return 'Topic';
					break;
					case 1:
						return 'Queue';
					break;
					default:
						return 'Generic';
				}
			break;
		}
		return false;
	}
}

?>