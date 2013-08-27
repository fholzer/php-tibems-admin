<?php

class TibcoConnections
{
	private $connections;

	function __construct()
	{
		$connections = tibcoadm_getconnections();
		sort($connections);
		foreach($connections as $connection)
		{
			$this->connections[] = new TibcoConnection($connection);
		}
	}

	public function getAll()
	{
		return $this->connections;
	}
}

?>