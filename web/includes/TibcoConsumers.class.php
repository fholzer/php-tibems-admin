<?php

class TibcoConsumers
{
	private $consumers;

	function __construct()
	{
		$consumers = tibcoadm_getconsumers();
		sort($consumers);
		foreach($consumers as $consumer)
		{
			$this->consumers[] = new TibcoConsumer($consumer);
		}
	}

	public function getAll()
	{
		return $this->consumers;
	}
}

?>