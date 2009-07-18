/***************************************************************************
 *   Copyright (C) 2009 by                                                 *
 *   Joris Guisson <joris.guisson@gmail.com>                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 ***************************************************************************/
#include <util/log.h>
#include "jobqueue.h"
#include "job.h"


namespace bt
{
	
	JobQueue::JobQueue(QObject* parent): QObject(parent)
	{

	}

	
	JobQueue::~JobQueue()
	{
		killAll();
	}
	
	void JobQueue::enqueue(Job* job)
	{
		queue.append(job);
		if (queue.count() == 1)
			startNextJob();
	}

	bool JobQueue::runningJobs() const
	{
		return queue.count() > 0;
	}
	
	Job* JobQueue::currentJob()
	{
		return queue.isEmpty() ? 0 : queue.front();
	}

	void JobQueue::startNextJob()
	{
		if (queue.isEmpty())
			return;
		
		Job* j = queue.front();
		connect(j,SIGNAL(result(KJob*)),this,SLOT(jobDone(KJob*)));
		j->start();
	}

	void JobQueue::jobDone(KJob* job)
	{
		if (queue.front() != job)
			return;
		
		if (job->error())
			Out(SYS_GEN|LOG_NOTICE) << "Job failed: " << job->errorString();
		
		// remove the job and start the next
		queue.pop_front();
		startNextJob();
	}
	
	
	void JobQueue::killAll()
	{
		if (queue.isEmpty())
			return;
		
		queue.front()->kill();
		qDeleteAll(queue);
	}

}

