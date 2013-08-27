<?php

class TibcoBridges
{
	private $bridges;

	function __construct()
	{
		$bridges = tibcoadm_getbridges();
		sort($bridges);
		foreach($bridges as $bridge)
		{
			$this->bridges[] = new TibcoBridge($bridge);
		}
	}

	public function getAll()
	{
		return $this->bridges;
	}

	public function getBridge($src, $srctype)
	{
		$data = tibcoadm_getbridge($src, $srctype);
		$i=0;
		while(is_array($data['bridge'.$i]))
		{
			$bridges[] = $data['bridge'.$i];
			$i++;
		}
		return array('source'=>array(dn=>$data['dn'], dt=>$data['dt']),'targets'=>$bridges);
	}
}

?>