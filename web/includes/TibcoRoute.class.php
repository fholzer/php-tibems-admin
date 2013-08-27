<?php

class TibcoRoute
{
	private $route;

	function __construct($route)
	{
		$this->route = $route;
	}

	public function getName()
	{
		return $this->route['name'];
	}

	public function getZoneName()
	{
		if($this->route['zoneName'] == NULL)
		{
			return 'default_mhop_zone';
		}
		return $this->route['zoneName'];
	}

	public function getUrl()
	{
		return $this->route['url'];
	}

	public function getZoneType()
	{
		return $this->route['zoneType'];
	}

	public function getZoneTypeString()
	{
		switch($this->route['zoneType'])
		{
			case 0:
				return 'm';
				break;
			case 1:
				return '1';
				break;
		}
		return 'u';
	}

	public function isStatic()
	{
		return $this->route['static'];
	}

	public function getConnID()
	{
		return $this->route['connid'];
	}
}

?>