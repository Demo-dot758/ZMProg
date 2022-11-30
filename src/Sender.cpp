#include "Sender.hh"

void Sender::Watching_and_Sending() 
{
    while (ShouldCountinueLooping()) 
    {
        if (!_pScn->IsChanged())
        { 
            usleep(10000); 
            continue; 
        }
        _pScn->LockAccess();
        
        //Wczytywanie listy obiektów
        ListOfMobileObj MobileObjects = _pScn->GetMobileObjMap();

        //Wektor wskazników na obiekty mobilne
        std::vector<std::shared_ptr<MobileObj>> ObjectsList;
        ListOfMobileObj::iterator iterator;
        for (iterator= MobileObjects.begin(); iterator != MobileObjects.end(); iterator++)
        {
                ObjectsList.push_back(iterator->second);
        }
        
        for (auto rObj : ObjectsList) 
        {
            std::string ObjState = rObj->GetStateDesc();
            cout << "Send: " << ObjState;
            Send(_Socket,ObjState.c_str());
        }
        
        _pScn->CancelChange();
        _pScn->UnlockAccess();
    }
}

int Send(int Sk2Server, const char *sMesg)
{
    ssize_t  IlWyslanych;
    ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

    while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) 
    {
        IlDoWyslania -= IlWyslanych;
        sMesg += IlWyslanych;
    }
    if (IlWyslanych < 0)
    {
        cerr << "*** Blad przeslania napisu." << endl;
    }
    return 0;
}

// bool ChangeState(Scene &Scn)
// {
//   bool Changed;

//   while (true) 
//   {
//     Scn.LockAccess(); // Zamykamy dostęp do sceny, gdy wykonujemy
//                             // modyfikacje na obiekcie.
//     for (MobileObj &rObj : Scn.MobileObjectsList) 
//     {
//         if (!(Changed = rObj.IncStateIndex())) 
//         {
//             Scn.UnlockAccess();
//             return false; 
//         }
//     }
//     Scn.MarkChange();
//     Scn.UnlockAccess();
//     usleep(300000);
//   }
//   return true;
// }

bool OpenConnection(int &rSocket)
{
    struct sockaddr_in  DaneAdSerw;

    bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

    DaneAdSerw.sin_family = AF_INET;
    DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
    DaneAdSerw.sin_port = htons(PORT);


    rSocket = socket(AF_INET,SOCK_STREAM,0);

    if (rSocket < 0) 
    {
        cerr << "*** Blad otwarcia gniazda." << endl;
        return false;
    }

    if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
    {
        cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
        return false;
    }
    return true;
}

void Fun_CommunicationThread(Sender  *pSender)
{
  pSender->Watching_and_Sending();
}
