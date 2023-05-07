#include "BugViewPanel.h"

void BugViewPanel::SetBug(Bug* NewBug)
{
	DisplayedBug = NewBug;
}

Bug* BugViewPanel::GetBug() const
{
	return DisplayedBug;
}
