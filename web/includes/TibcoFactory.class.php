<?php

class TibcoFactory
{
	private $factory;

	function __construct($factory)
	{
		$this->factory = $factory;
	}

	public function getUrl()
	{
		return $this->factory['url'];
	}
	
	public function getFt()
	{
		return $this->factory['ft'];
	}
	
	public function getXa()
	{
		return $this->factory['xa'];
	}
	
	public function getAset()
	{
		return $this->factory['aset'];
	}

	public function getFtype()
	{
		switch($this->factory['ft'])
		{
			case 0:
				return 'GenericConnectionFactory';
				break;
			case 1:
				return (($this->getXa())?'XA':'').'QueueConnectionFactory';
				break;
			case 2:
				return (($this->getXa())?'XA':'').'TopicConnectionFactory';
				break;
		}
	}
}

?>