<?php

class TibcoTopic
{
	private $topic;
	private $implist;
	private $explist;

	function __construct($topic)
	{
		$this->topic = $topic;
	}

	public function getDn()
	{
		return $this->topic['dn'];
	}
	
	public function getCc()
	{
		return $this->topic['cc'];
	}
	
	public function getNm()
	{
		return $this->topic['nm'];
	}
	
	public function getPf()
	{
		return $this->topic['pf'];
	}
	
	public function getMb()
	{
		return $this->topic['mb'];
	}
	
	public function getMm()
	{
		return $this->topic['mm'];
	}
	
	public function getOp()
	{
		return $this->topic['op'];
	}
	
	public function getExpy()
	{
		return $this->topic['expy'];
	}
	
	public function getCd()
	{
		return $this->topic['cd'];
	}
	
	public function getPs()
	{
		return bytes($this->topic['ps']);
	}
	
	public function getFcs()
	{
		return $this->topic['fcs'];
	}

	public function destType()
	{
		return ($this->topic['props'] & 0x1) == 0 ? 2 : 1;
	}

	public function isTemporary()
	{
		return ($this->topic['props'] & 0x2) != 0;
	}

	public function isStatic()
	{
		return ($this->topic['props'] & 0x4) != 0;
	}

	public function isExported()
	{
		return ($this->topic['props'] & 0x8) != 0;
	}

	public function isExportedInherited()
	{
		return ($this->topic['props'] & 0x10) != 0;
	}

	public function isImported()
	{
		return ($this->topic['props'] & 0x20) != 0;
	}

	public function isImportedInherited()
	{
		return ($this->topic['props'] & 0x40) != 0;
	}

	public function isExclusive()
	{
		return ($this->topic['props'] & 0x80) != 0;
	}

	public function isExclusiveInherited()
	{
		return ($this->topic['props'] & 0x100) != 0;
	}

	public function isFailsafe()
	{
		return ($this->topic['props'] & 0x200) != 0;
	}

	public function isFailsafeInherited()
	{
		return ($this->topic['props'] & 0x400) != 0;
	}

	public function isGlobal()
	{
		return ($this->topic['props'] & 0x800) != 0;
	}

	public function isGlobalInherited()
	{
		return ($this->topic['props'] & 0x1000) != 0;
	}

	public function isSecure()
	{
		return ($this->topic['props'] & 0x2000) != 0;
	}

	public function isSecureInherited()
	{
		return ($this->topic['props'] & 0x4000) != 0;
	}

	public function maxBytesInherited()
	{
		return ($this->topic['props'] & 0x20000) != 0;
	}

	public function senderName()
	{
		return ($this->topic['props'] & 0x1000000) != 0;
	}

	public function senderNameInherited()
	{
		return ($this->topic['props'] & 0x2000000) != 0;
	}

	public function senderNameEnforced()
	{
		return ($this->topic['props'] & 0x4000000) != 0;
	}

	public function senderNameEnforcedInherited()
	{
		return ($this->topic['props'] & 0x8000000) != 0;
	}

	public function isBridged()
	{
		return ($this->topic['props'] & 0x10000000) != 0;
	}

	public function isBridgedInherited()
	{
		return ($this->topic['props'] & 0x20000000) != 0;
	}

	public function fcBytesInherited()
	{
		return ($this->topic['propsex'] & 0x1) != 0;
	}

	public function traceInherited()
	{
		return ($this->topic['propsex'] & 0x4) != 0;
	}

	public function expiryInherited()
	{
		return ($this->topic['propsex'] & 0x8) != 0;
	}

	public function maxMsgsInherited()
	{
		return ($this->topic['propsex'] & 0x10) != 0;
	}

	public function overflowPolicyInherited()
	{
		return ($this->topic['propsex'] & 0x20) != 0;
	}

	public function prefetchInherited()
	{
		return ($this->topic['props'] & 0x40000) != 0;
	}
	
	public function getImportTransports()
	{
		if(!is_array($this->implist))
		{
			$this->implist = $this->topic['implist'];
		}
		return $this->implist;
	}
	
	public function getExportTransports()
	{
		if(!is_array($this->explist))
		{
			$this->explist = $this->topic['explist'];
		}
		return $this->explist;
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
		if(is_array($this->getExportTransports())) $propstring .= '+';
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