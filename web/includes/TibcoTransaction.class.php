<?php

class TibcoTransaction
{
	private $transaction;

	function __construct($transaction)
	{
		$this->transaction = $transaction;
	}

	function getFormatId()
	{
		return $this->transaction['formatId'];
	}

	function getGrId()
	{
		return $this->transaction['globalTxIdLength'];
	}

	function getBytes()
	{
		return $this->transaction['bytes'];
	}

	function getState()
	{
		return $this->transaction['state'];
	}

	function getBranchQualLength()
	{
		return $this->transaction['branchQualLength'];
	}

	function getGlobalTxId()
	{
		return $this->transaction['globalTxId'];
	}

	function getBranchQual()
	{
		return $this->transaction['branchQual'];
	}
}

?>