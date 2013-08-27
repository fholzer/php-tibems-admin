<?php

class TibcoRoutes
{
	private $routes;

	function __construct()
	{
		$routes = tibcoadm_getroutes();
		sort($routes);
		foreach($routes as $route)
		{
			$this->routes[] = new TibcoRoute($route);
		}
	}

	public function getAll()
	{
		return $this->routes;
	}
}

?>