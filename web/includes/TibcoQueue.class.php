<?php

class TibcoQueue
{
	private $queue;
	private $implist;

	function __construct($queue)
	{
		$this->queue = $queue;
	}

	public function getDn()
	{
		return $this->queue['dn'];
	}
	
	public function getCc()
	{
		return $this->queue['cc'];
	}
	
	public function getNm()
	{
		return $this->queue['nm'];
	}
	
	public function getPf()
	{
		return $this->queue['pf'];
	}
	
	public function getMb()
	{
		return $this->queue['mb'];
	}
	
	public function getMm()
	{
		return $this->queue['mm'];
	}
	
	public function getOp()
	{
		return $this->queue['op'];
	}
	
	public function getMrd()
	{
		return $this->queue['mrd'];
	}
	
	public function getExpy()
	{
		return $this->queue['expy'];
	}
	
	public function getPs()
	{
		return bytes($this->queue['ps']);
	}

	public function getFcs()
	{
		return $this->queue['fcs'];
	}

	public function destType()
	{
		return ($this->queue['props'] & 0x1) == 0 ? 2 : 1;
	}

	public function isTemporary()
	{
		return ($this->queue['props'] & 0x2) != 0;
	}

	public function isStatic()
	{
		return ($this->queue['props'] & 0x4) != 0;
	}

	public function isExported()
	{
		return ($this->queue['props'] & 0x8) != 0;
	}

	public function isExportedInherited()
	{
		return ($this->queue['props'] & 0x10) != 0;
	}

	public function isImported()
	{
		return ($this->queue['props'] & 0x20) != 0;
	}

	public function isImportedInherited()
	{
		return ($this->queue['props'] & 0x40) != 0;
	}

	public function isExclusive()
	{
		return ($this->queue['props'] & 0x80) != 0;
	}

	public function isExclusiveInherited()
	{
		return ($this->queue['props'] & 0x100) != 0;
	}

	public function isFailsafe()
	{
		return ($this->queue['props'] & 0x200) != 0;
	}

	public function isFailsafeInherited()
	{
		return ($this->queue['props'] & 0x400) != 0;
	}

	public function isGlobal()
	{
		return ($this->queue['props'] & 0x800) != 0;
	}

	public function isGlobalInherited()
	{
		return ($this->queue['props'] & 0x1000) != 0;
	}

	public function isSecure()
	{
		return ($this->queue['props'] & 0x2000) != 0;
	}

	public function isSecureInherited()
	{
		return ($this->queue['props'] & 0x4000) != 0;
	}

	public function maxBytesInherited()
	{
		return ($this->queue['props'] & 0x20000) != 0;
	}

	public function senderName()
	{
		return ($this->queue['props'] & 0x1000000) != 0;
	}

	public function senderNameInherited()
	{
		return ($this->queue['props'] & 0x2000000) != 0;
	}

	public function senderNameEnforced()
	{
		return ($this->queue['props'] & 0x4000000) != 0;
	}

	public function senderNameEnforcedInherited()
	{
		return ($this->queue['props'] & 0x8000000) != 0;
	}

	public function isBridged()
	{
		return ($this->queue['props'] & 0x10000000) != 0;
	}

	public function isBridgedInherited()
	{
		return ($this->queue['props'] & 0x20000000) != 0;
	}

	public function fcBytesInherited()
	{
		return ($this->queue['propsex'] & 0x1) != 0;
	}

	public function traceInherited()
	{
		return ($this->queue['propsex'] & 0x4) != 0;
	}

	public function expiryInherited()
	{
		return ($this->queue['propsex'] & 0x8) != 0;
	}

	public function maxMsgsInherited()
	{
		return ($this->queue['propsex'] & 0x10) != 0;
	}

	public function overflowPolicyInherited()
	{
		return ($this->queue['propsex'] & 0x20) != 0;
	}

	public function prefetchInherited()
	{
		return ($this->queue['props'] & 0x40000) != 0;
	}
	
	public function getImportTransports()
	{
		if(!is_array($this->implist))
		{
			$this->implist = $this->queue['implist'];
		}
		return $this->implist;
	}
	
	public function getProps()
	{
		$propstring = '';
		if($this->isSecure()) $propstring .= '+';
		elseif($this->isSecureInherited()) $propstring .= '*';
		else $propstring .= '-';
		if($this->senderName()) $propstring .= '+';
		elseif($this->senderNameInherited()) $propstring .= '*';
		else $propstring .= '-';
		if($this->isFailsafe()) $propstring .= '+';
		elseif($this->isFailsafeInherited()) $propstring .= '*';
		else $propstring .= '-';
		if($this->isGlobal()) $propstring .= '+';
		elseif($this->isGlobalInherited()) $propstring .= '*';
		else $propstring .= '-';
		if($this->isExclusive()) $propstring .= '+';
		elseif($this->isExclusiveInherited()) $propstring .= '*';
		else $propstring .= '-';
		if(is_array($this->getImportTransports())) $propstring .= '+';
		else $propstring .= '-';
		if($this->isBridged()) $propstring .= '+';
		elseif($this->isBridgedInherited()) $propstring .= '*';
		else $propstring .= '-';
		if($this->fcBytesInherited()) $propstring .= '+';
		else $propstring .= '-';
		if($this->traceInherited()) $propstring .= '+';
		else $propstring .= '-';
		return $propstring;
	}
}

?>