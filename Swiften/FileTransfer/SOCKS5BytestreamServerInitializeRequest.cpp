/*
 * Copyright (c) 2012 Remko Tronçon
 * Licensed under the GNU General Public License v3.
 * See Documentation/Licenses/GPLv3.txt for more information.
 */

#include <Swiften/FileTransfer/SOCKS5BytestreamServerInitializeRequest.h>

#include <boost/bind.hpp>

#include <Swiften/FileTransfer/SOCKS5BytestreamServerManager.h>

using namespace Swift;

SOCKS5BytestreamServerInitializeRequest::SOCKS5BytestreamServerInitializeRequest(SOCKS5BytestreamServerManager* manager) : manager(manager) {
}

SOCKS5BytestreamServerInitializeRequest::~SOCKS5BytestreamServerInitializeRequest() {
}

void SOCKS5BytestreamServerInitializeRequest::start() {
	if (manager->isInitialized()) {
		handleInitialized(true);
	}
	else {
		manager->onInitialized.connect(
				boost::bind(&SOCKS5BytestreamServerInitializeRequest::handleInitialized, this, _1));
		manager->initialize();
	}
}

void SOCKS5BytestreamServerInitializeRequest::stop() {
	manager->onInitialized.disconnect(
			boost::bind(&SOCKS5BytestreamServerInitializeRequest::handleInitialized, this, _1));
}

void SOCKS5BytestreamServerInitializeRequest::handleInitialized(bool success) {
	onFinished(success);
}
