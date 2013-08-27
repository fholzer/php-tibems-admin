<?php

class TibcoProducers
{
	private $producers;

	function __construct()
	{
		$producers = tibcoadm_getproducersstatistics();
		sort($producers);
		foreach($producers as $producer)
		{
			$this->producers[] = new TibcoProducer($producer);
		}
	}

	public function getAll()
	{
		return $this->producers;
	}
}

?>