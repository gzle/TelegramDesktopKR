/*
This file is part of Telegram Desktop,
an unofficial desktop messaging app, see https://telegram.org

Telegram Desktop is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

It is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

Full license: https://github.com/telegramdesktop/tdesktop/blob/master/LICENSE
Copyright (c) 2014 John Preston, https://tdesktop.com
*/
#pragma once

#include <QtWidgets/QWidget>
#include "gui/flatbutton.h"
#include "gui/flatinput.h"
#include "intro.h"

class CodeInput : public FlatInput {
	Q_OBJECT

public:

	CodeInput(QWidget *parent, const style::flatInput &st, const QString &ph);

signals:

	void codeEntered();

protected:

	void correctValue(QKeyEvent *e, const QString &was);

};

class IntroCode : public IntroStage, public Animated, public RPCSender {
	Q_OBJECT

public:

	IntroCode(IntroWidget *parent);

	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);

	bool animStep(float64 ms);

	void activate();
	void deactivate();
	void onNext();
	void onBack();

	void codeSubmitDone(const MTPauth_Authorization &result);
	bool codeSubmitFail(const RPCError &error);

public slots:

	void onSubmitCode(bool force = false);
	void onInputChange();
	void onSendCall();
	void onCheckRequest();

private:

	void showError(const QString &err);
	void callDone(const MTPBool &v);
	void stopCheck();

	QString error;
	anim::fvalue errorAlpha;

	FlatButton next, back;

	QRect textRect;

	CodeInput code;
	QString sentCode;
	mtpRequestId sentRequest;
	QTimer callTimer;
	int32 waitTillCall;

	QTimer checkRequest;
};
