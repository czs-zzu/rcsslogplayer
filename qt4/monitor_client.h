// -*-c++-*-

/*!
  \file monitor_client.h
  \brief Monitor Client class Header File.
*/

/*
 *Copyright:

 Copyright (C) The RoboCup Soccer Server Maintenance Group.
 Hidehisa AKIYAMA

 This code is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2, or (at your option)
 any later version.

 This code is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this code; see the file COPYING.  If not, write to
 the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.

 *EndCopyright:
 */

/////////////////////////////////////////////////////////////////////

#ifndef RCSSLOGPLAYER_MONITOR_CLIENT_H
#define RCSSLOGPLAYER_MONITOR_CLIENT_H

#include <QObject>

#include <rcsslogplayer/types.h>

#include <boost/scoped_ptr.hpp>

class QHostInfo;
class QTimer;
class QUdpSocket;
class QSocketNotifier;
class DispHolder;

class MonitorClientImpl;

//! monitor client that connect to the rcssserver
class MonitorClient
    : public QObject {

    Q_OBJECT

private:

    boost::scoped_ptr< MonitorClientImpl > M_impl;

    DispHolder & M_disp_holder;

    QUdpSocket * M_socket;
    QTimer * M_timer;

    int M_version; //!< protocol version

    int M_waited_msec;


    //! not used
    MonitorClient();
    MonitorClient( const MonitorClient & );
    MonitorClient & operator=( const MonitorClient & );
public:
    //! constructor
    MonitorClient( DispHolder & disp_holder,
                   const char * hostname,
                   const int port,
                   const int version );

    ~MonitorClient();

    void disconnect();

    bool isConnected() const;

private:

    void sendCommand( const std::string & com );

public:

    // monitor command

    void sendDispInit();
    void sendDispBye();
    void sendKickOff();
    void sendFreeKick( const double & x,
                       const double & y,
                       const rcss::rcg::Side side );
    void sendDropBall( const double & x,
                       const double & y )
      {
          sendFreeKick( x, y, rcss::rcg::NEUTRAL );
      }
    void sendFreeKickLeft( const double & x,
                           const double & y )
      {
          sendFreeKick( x, y, rcss::rcg::LEFT );
      }
    void sendFreeKickRight( const double & x,
                            const double & y )
      {
          sendFreeKick( x, y, rcss::rcg::RIGHT );
      }

    void sendMove( const rcss::rcg::Side side,
                   const int unum,
                   const double & x,
                   const double & y,
                   const double & angle );

    void sendDiscard( const rcss::rcg::Side side,
                      const int unum );


    // trainer command

    void sendChangeMode( const rcss::rcg::PlayMode pmode );

    void sendTrainerMoveBall( const double & x,
                              const double & y );

    void sendTrainerMoveBall( const double & x,
                              const double & y,
                              const double & vx,
                              const double & vy );

    void sendTrainerMovePlayer( const std::string & team_name,
                                const int unum,
                                const double & x,
                                const double & y );
    void sendTrainerMovePlayer( const std::string & team_name,
                                const int unum,
                                const double & x,
                                const double & y,
                                const double & angle );
    void sendTrainerMovePlayer( const std::string & team_name,
                                const int unum,
                                const double & x,
                                const double & y,
                                const double & angle,
                                const double & vx,
                                const double & vy );


    void sendRecover();

    void sencChangePlayerType( const std::string & team_name,
                               const int unum,
                               const int type );

    void sendCheckBal();

private slots:

    void handleReceive();
    void handleTimer();


signals:

    void received();
    void timeout();

};

#endif