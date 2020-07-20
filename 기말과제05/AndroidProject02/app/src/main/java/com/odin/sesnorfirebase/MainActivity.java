package com.odin.sesnorfirebase;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.ListView;

import com.google.firebase.database.ChildEventListener;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class MainActivity extends AppCompatActivity {

        FirebaseDatabase db = FirebaseDatabase.getInstance(); // Realtime에서 데이터를 가져오기 위해 데이터레퍼런스를 찾아서 가져옴
    DatabaseReference myRef = db.getReference ("logDHT"); // logDHT의 값들을 가져옴

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final ListViewAdapter adpater = new ListViewAdapter(); // 리스트뷰 어댑터 선언
        final ListView listView; //리스트뷰 선언

        listView = (ListView) findViewById(R.id.listView); // 리스트뷰를 레이아웃에서 값을 찾아옴
        listView.setAdapter(adpater); // 리스트뷰와 어뎁터를 연결함


        myRef.addChildEventListener(new ChildEventListener() {
            @Override
            public void onChildAdded(@NonNull DataSnapshot dataSnapshot, @Nullable String s) {
                String data1 = dataSnapshot.child("humidity").getValue().toString(); // data1에는 습도 값을 넣어라
                String data2 = dataSnapshot.child("temperature").getValue().toString(); // data2에는 온도 값을 넣어라
                String data3 = dataSnapshot.child("time").getValue().toString(); // data3에는 시간 값을 넣어라

                adpater.addItem("습도 : " + data1.toString(),"온도 : " + data2.toString(), "시간 : " + data3.toString()); // 습도 :
                listView.setAdapter(adpater); // 리스트뷰에 위 ㅔ아이템 들을 세팅하게 만듬


            }

            @Override
            public void onChildChanged(DataSnapshot dataSnapshot, String s) { }

            @Override
            public void onChildRemoved(DataSnapshot dataSnapshot) { }

            @Override
            public void onChildMoved(DataSnapshot dataSnapshot, String s) { }

            @Override
            public void onCancelled(DatabaseError databaseError) { }
        });


    }
}