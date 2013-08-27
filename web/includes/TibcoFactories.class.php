<?php

class TibcoFactories
{
	private $factories;

	function __construct()
	{
		$factories = tibcoadm_getfactories();
		sort($factories);
		foreach($factories as $factory)
		{
			$this->factories[] = new TibcoFactory($factory);
		}
	}

	public function getAll()
	{
		return $this->factories;
	}
}

?>