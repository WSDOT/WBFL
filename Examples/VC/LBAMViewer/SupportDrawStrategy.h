#pragma once

interface iSupportDrawStrategy
{
   virtual void SetSupport(ISupport* jnt, IDType supportID) = 0;
};

