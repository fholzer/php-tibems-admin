<?php

class TibcoJndiNames
{
	private $jndinames;

	function __construct()
	{
		$jndinames = tibcoadm_getjndinames();
		sort($jndinames);
		foreach($jndinames as $jndiname)
		{
			$this->jndinames[] = new TibcoJndiName($jndiname);
		}
	}

	public function getAll()
	{
		return $this->jndinames;
	}
}

?>