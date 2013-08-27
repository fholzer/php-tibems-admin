<?php

class TibcoTopics
{
	private $topics;

	function __construct()
	{
		$topics = tibcoadm_gettopics();
		sort($topics);
		foreach($topics as $topic)
		{
			$this->topics[] = new TibcoTopic($topic);
		}
	}

	public function getAll()
	{
		return $this->topics;
	}

	public function getTopic($name)
	{
		$topic = tibcoadm_gettopics($name);
		return new TibcoTopic($topic[$name]);
	}

}

?>