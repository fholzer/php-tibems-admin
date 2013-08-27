<?php

class TibcoDurables
{
	private $durables;

	function __construct()
	{
		$durables = tibcoadm_getdurables();
		sort($durables);
		foreach($durables as $durable)
		{
			$this->durables[] = new TibcoDurable($durable);
		}
	}

	public function getAll()
	{
		return $this->durables;
	}
}

?>