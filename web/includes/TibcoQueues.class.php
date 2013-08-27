<?php

class TibcoQueues
{
	private $queues;

	function __construct()
	{
		$queues = tibcoadm_getqueues();
		sort($queues);
		foreach($queues as $queue)
		{
			$this->queues[] = new TibcoQueue($queue);
		}
	}

	public function getAll()
	{
		return $this->queues;
	}

	public function getQueue($name)
	{
		$queue = tibcoadm_getqueues($name);
		return new TibcoQueue($queue[$name]);
	}
}

?>