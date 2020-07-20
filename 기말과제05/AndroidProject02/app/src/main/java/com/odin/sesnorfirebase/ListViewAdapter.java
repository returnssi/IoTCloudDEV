package com.odin.sesnorfirebase;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class ListViewAdapter extends BaseAdapter {

    public ArrayList<ListViewItem> listViewItemList = new ArrayList<ListViewItem>();


    @Override
    public int getCount() {
        return listViewItemList.size();
    }

    @Override
    public Object getItem(int position) {
        return listViewItemList.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        final int pos = position;
        final Context context = parent.getContext();

        // "listview_item" Layout을 inflate하여 convertView 참조 획득.
        if (convertView == null) {
            LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = inflater.inflate(R.layout.listview_item, parent, false);
        }

        // 화면에 표시될 View(Layout이 inflate된)으로부터 위젯에 대한 참조 획득
        TextView tvhumidity = (TextView) convertView.findViewById(R.id.tvhumidity);
        TextView tvtemperature = (TextView) convertView.findViewById(R.id.tvtemperature);
        TextView tvTime = (TextView) convertView.findViewById(R.id.tvtime);
        // Data Set(filteredItemList)에서 position에 위치한 데이터 참조 획득
        ListViewItem listViewItem = listViewItemList.get(position);

        tvhumidity.setText(listViewItem.getHumidity());
        tvtemperature.setText(listViewItem.getTemperature());
        tvTime.setText(listViewItem.getTime());

        return convertView;
    }

    public void addItem(String data1, String data2, String data3) {
        ListViewItem item = new ListViewItem();
        item.setHumidity(data1);
        item.setTemperature(data2);
        item.setTime(data3);

        listViewItemList.add(item);
    }
}

    /*public void clearItem(){
        listViewItemList.clear();
    }
}*/
